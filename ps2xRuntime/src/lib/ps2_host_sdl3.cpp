#include "ps2_host_sdl3.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>  
 #include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

static_assert(KEY_A == SDL_SCANCODE_A && KEY_Z == SDL_SCANCODE_Z && KEY_ONE == SDL_SCANCODE_1 &&
              KEY_THREE == SDL_SCANCODE_3 && KEY_ENTER == SDL_SCANCODE_RETURN && KEY_ESCAPE == SDL_SCANCODE_ESCAPE &&
              KEY_BACKSPACE == SDL_SCANCODE_BACKSPACE && KEY_TAB == SDL_SCANCODE_TAB && KEY_SPACE == SDL_SCANCODE_SPACE &&
              KEY_F1 == SDL_SCANCODE_F1 && KEY_F2 == SDL_SCANCODE_F2 && KEY_F9 == SDL_SCANCODE_F9 &&
              KEY_F10 == SDL_SCANCODE_F10 && KEY_RIGHT == SDL_SCANCODE_RIGHT && KEY_LEFT == SDL_SCANCODE_LEFT &&
              KEY_DOWN == SDL_SCANCODE_DOWN && KEY_UP == SDL_SCANCODE_UP && KEY_KP_ENTER == SDL_SCANCODE_KP_ENTER &&

              KEY_KP_1 == SDL_SCANCODE_KP_1 && KEY_KP_2 == SDL_SCANCODE_KP_2 && KEY_KP_4 == SDL_SCANCODE_KP_4 &&

              KEY_KP_6 == SDL_SCANCODE_KP_6 && KEY_KP_7 == SDL_SCANCODE_KP_7 && KEY_KP_8 == SDL_SCANCODE_KP_8 &&
              KEY_KP_9 == SDL_SCANCODE_KP_9 && KEY_KP_0 == SDL_SCANCODE_KP_0 &&
              KEY_LEFT_CONTROL == SDL_SCANCODE_LCTRL && KEY_LEFT_SHIFT == SDL_SCANCODE_LSHIFT &&
              KEY_LEFT_ALT == SDL_SCANCODE_LALT && KEY_RIGHT_CONTROL == SDL_SCANCODE_RCTRL &&
              KEY_RIGHT_SHIFT == SDL_SCANCODE_RSHIFT,
              "ps2_host_sdl3.h key values must be SDL scancodes");

namespace
{   
constexpr int kMaxGamepads = 4;

struct Host
{
    unsigned int configFlags = 0;
    bool windowOnly = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool closeRequested = false;
    Uint64 startNs = 0;
    int targetFps = 0;
    Uint64 nextFrameNs = 0;
    std::string baseDirectory;
    void (*eventHook)(const SDL_Event *) = nullptr;
    // Window thread only.
    std::array<bool, SDL_SCANCODE_COUNT> pressed{};

    Vector2 mouseDelta{};
    SDL_Gamepad *gamepads[kMaxGamepads]{};
    uint32_t rumbleSent = 0;
    Uint64 rumbleSentNs = 0;

    bool audioReady = false;
} s_host;

// Input copied by the window thread after each event read, for any thread.

std::array<std::atomic<bool>, SDL_SCANCODE_COUNT> s_keyDown{};
std::atomic<uint32_t> s_mouseButtons{0};
struct GamepadState
{
    std::atomic<bool> available{false};  
    std::atomic<uint32_t> buttons{0}; // bit =  GamepadButton
    std::atomic<float> axes[6]{};
};
GamepadState s_gamepadState[kMaxGamepads];
// ps2HostSetUiCapture, and ps2HostSetRumble's motors (low 16 bits big, high 16 bits small).
std::atomic<bool> s_uiKeyboard{false};
std::atomic<bool> s_uiMouse{false};
std::atomic<uint32_t> s_rumble{0};

SDL_GamepadButton sdlButton(int button)
{  
    switch (button)
    {
    case GAMEPAD_BUTTON_LEFT_FACE_UP: return SDL_GAMEPAD_BUTTON_DPAD_UP;
    case GAMEPAD_BUTTON_LEFT_FACE_RIGHT: return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
    case GAMEPAD_BUTTON_LEFT_FACE_DOWN: return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
    case GAMEPAD_BUTTON_LEFT_FACE_LEFT: return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
    case GAMEPAD_BUTTON_RIGHT_FACE_UP: return SDL_GAMEPAD_BUTTON_NORTH;
    case GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: return SDL_GAMEPAD_BUTTON_EAST;
    case GAMEPAD_BUTTON_RIGHT_FACE_DOWN: return SDL_GAMEPAD_BUTTON_SOUTH;
    case GAMEPAD_BUTTON_RIGHT_FACE_LEFT: return SDL_GAMEPAD_BUTTON_WEST;
    case GAMEPAD_BUTTON_LEFT_TRIGGER_1: return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;

    case GAMEPAD_BUTTON_RIGHT_TRIGGER_1: return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
    case GAMEPAD_BUTTON_MIDDLE_LEFT: return SDL_GAMEPAD_BUTTON_BACK;
    case GAMEPAD_BUTTON_MIDDLE: return SDL_GAMEPAD_BUTTON_GUIDE;

    case GAMEPAD_BUTTON_MIDDLE_RIGHT: return SDL_GAMEPAD_BUTTON_START;
    case GAMEPAD_BUTTON_LEFT_THUMB: return SDL_GAMEPAD_BUTTON_LEFT_STICK;
    case GAMEPAD_BUTTON_RIGHT_THUMB: return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
    default: return SDL_GAMEPAD_BUTTON_INVALID;
    }
}

// raylib's range: sticks -1..1, triggers -1 (released) .. 1.
float axisValue(SDL_Gamepad *pad, int axis)
{
    static constexpr SDL_GamepadAxis kAxes[6] = {SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY,
                                                 SDL_GAMEPAD_AXIS_RIGHTX, SDL_GAMEPAD_AXIS_RIGHTY,
                                                 SDL_GAMEPAD_AXIS_LEFT_TRIGGER, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER};  
    const float v = std::clamp(float(SDL_GetGamepadAxis(pad, kAxes[axis])) / 32767.0f, -1.0f, 1.0f);
    return axis >= GAMEPAD_AXIS_LEFT_TRIGGER ? v * 2.0f - 1.0f : v;
}

void copyGamepads()
{
    for (int i = 0; i < kMaxGamepads; ++i)
    {
        GamepadState &state = s_gamepadState[i];
        SDL_Gamepad *pad = s_host.gamepads[i] ;
        if (!pad)
        {
            state.available.store(false, std::memory_order_relaxed);
            state.buttons.store(0, std::memory_order_relaxed);
            continue;
        }

        float axes[6];
         for (int a = 0; a < 6; ++a)
        {
            axes[a] = axisValue(pad, a);
            state.axes[a].store(axes[a], std::memory_order_relaxed);
         }
        uint32_t buttons =  0;
        for (int b = GAMEPAD_BUTTON_LEFT_FACE_UP; b <= GAMEPAD_BUTTON_RIGHT_THUMB; ++b)
        {
            const SDL_GamepadButton button = sdlButton(b);
            if (button != SDL_GAMEPAD_BUTTON_INVALID && SDL_GetGamepadButton(pad, button))
                buttons |= 1u << b;

         }
        constexpr float kTriggerPressed = 0.12f * 2.0f - 1.0f;
        if (axes[GAMEPAD_AXIS_LEFT_TRIGGER] > kTriggerPressed)
             buttons |= 1u << GAMEPAD_BUTTON_LEFT_TRIGGER_2;
        if (axes[GAMEPAD_AXIS_RIGHT_TRIGGER] > kTriggerPressed)  
            buttons |= 1u << GAMEPAD_BUTTON_RIGHT_TRIGGER_2;   

        state.buttons.store(buttons, std::memory_order_relaxed);
        state.available.store(true, std::memory_order_release);
    }  
}

void applyRumble()
{
    SDL_Gamepad *pad = s_host.gamepads[0];  
    static const bool scripted = std::getenv("PS2_PAD_SCRIPT") != nullptr;

    if (!pad || scripted)
    {
        s_host.rumbleSent = 0;
        return;
     }
    const uint32_t want = s_rumble.load(std::memory_order_relaxed);
    const Uint64 now = SDL_GetTicksNS();
    if (want == s_host.rumbleSent && (want == 0 || now - s_host.rumbleSentNs < 500000000ull))   
        return;
    SDL_RumbleGamepad(pad, Uint16(want & 0xFFFFu), Uint16(want >> 16), 1000);

    s_host.rumbleSent = want;
    s_host.rumbleSentNs = now;
}

void handleEvent(const SDL_Event &e)
{
    switch (e.type)
     {
    case SDL_EVENT_QUIT:
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        s_host.closeRequested = true;
        break;
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        if (e.key.scancode > SDL_SCANCODE_UNKNOWN && e.key.scancode < SDL_SCANCODE_COUNT)
        {
            if (e.key.down && !e.key.repeat)
                s_host.pressed[e.key.scancode] = true;
            s_keyDown[e.key.scancode].store(e.key.down, std::memory_order_relaxed);

        } 
        break;

    case SDL_EVENT_WINDOW_FOCUS_LOST:
        // Keys released while another window has the focus send no event.
        for (auto &key : s_keyDown)
            key.store(false, std::memory_order_relaxed);
        s_mouseButtons.store(0, std::memory_order_relaxed);
        break;
    case SDL_EVENT_MOUSE_MOTION:
        s_host.mouseDelta.x += e.motion.xrel;
        s_host.mouseDelta.y += e.motion.yrel;
         break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
    {
        const int bit = e.button.button == SDL_BUTTON_LEFT ? 1 : e.button.button == SDL_BUTTON_RIGHT ? 2   
                                                           : e.button.button == SDL_BUTTON_MIDDLE  ? 4
                                                                                                   : 0;
        if (bit)
        {
            if (e.button.down)
                s_mouseButtons.fetch_or(uint32_t(bit), std::memory_order_relaxed);
            else
                s_mouseButtons.fetch_and(~uint32_t(bit), std::memory_order_relaxed);
        }
        break;
    }
    case SDL_EVENT_GAMEPAD_ADDED:
    {
        for (SDL_Gamepad *pad : s_host.gamepads)
            if (pad && SDL_GetGamepadID(pad) == e.gdevice.which)
                return;
        for (SDL_Gamepad *&pad : s_host.gamepads)
            if (!pad)
            {
                pad = SDL_OpenGamepad(e.gdevice.which);
                if (pad)
                    std::fprintf(stderr, "[input] gamepad: %s\n", SDL_GetGamepadName(pad));
                break;
            }
        break;
    }
    case SDL_EVENT_GAMEPAD_REMOVED:   
        for (SDL_Gamepad *&pad : s_host.gamepads)
            if (pad && SDL_GetGamepadID(pad) == e.gdevice.which)

            {
                SDL_CloseGamepad(pad);
                pad = nullptr;
            }
        break;
    default:
        break;
    }
}

void pollEvents()
{
    s_host.pressed.fill(false);
    s_host.mouseDelta =  {0.0f, 0.0f};
    SDL_Event e;
     while (SDL_PollEvent(&e))
    {
        handleEvent(e);   
        if (s_host.eventHook)  
            s_host.eventHook(&e);
    }
    copyGamepads();
     applyRumble();
}

void setDrawColor(Color c)
{
    SDL_SetRenderDrawBlendMode(s_host.renderer, c.a == 255 ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(s_host.renderer, c.r, c.g, c.b, c.a);
}  

int textScale(int fontSize)
{
    return std::max(1, int(std::lround(fontSize / 10.0)));
}

struct StreamData
{
    SDL_AudioStream *stream = nullptr;
    std::atomic<AudioCallback> callback{nullptr};

};  

// SDL's audio thread: the stream wants `additional` more bytes.
void audioCallback(void *userdata, SDL_AudioStream *stream, int additional, int /*total*/)
{
     const AudioCallback callback = static_cast<StreamData *>(userdata)->callback.load(std::memory_order_acquire);
    if (!callback || additional <= 0)
        return;
    thread_local std::vector<int16_t> buffer;   
    const unsigned frames = unsigned(additional + 3) / 4u; // 16-bit stereo
    buffer.resize(size_t(frames) * 2u);
    callback(buffer.data(), frames);
    SDL_PutAudioStreamData(stream, buffer.data(), int(frames * 4u));
}

// A Sound: its own device stream, and the PCM that PlaySound puts in again.
struct SoundData
{
    SDL_AudioStream *stream = nullptr;
    std::vector<Uint8> pcm;
};

SoundData *soundData(const Sound &sound)
{

    return static_cast<SoundData *>(sound.stream.handle);
}
} // namespace

 void SetConfigFlags(unsigned int flags)
{
    s_host.configFlags =  flags;
}

void InitWindow(int width, int height, const char *title)
{

    if (s_host.window)
        return;
    // Gamepads keep working while another window has the focus (as GLFW).
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::fprintf(stderr, "[host] SDL_Init failed: %s\n", SDL_GetError());
        return;
    }
    s_host.startNs = SDL_GetTicksNS();  
    SDL_WindowFlags flags = (s_host.configFlags & FLAG_WINDOW_RESIZABLE) ? SDL_WINDOW_RESIZABLE : 0;
    if (const char *v = std::getenv("PS2_WINDOW_BACKGROUND"); v && *v == '1')
    {   
        SDL_SetHint(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, "0");
        flags |= SDL_WINDOW_MINIMIZED;
    }
    // PS2_WINDOW_MAXIMIZED=1 (benchmarks): the window starts maximized.
    else if (const char *m = std::getenv("PS2_WINDOW_MAXIMIZED"); m && *m == '1')
         flags |= SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;

    if (s_host.windowOnly)
    {
        // Only the window: another renderer presents to it (ps2HostSetWindowOnly). 
        s_host.window = SDL_CreateWindow(title ? title : "", width, height, flags);

        if (!s_host.window)
        {
            std::fprintf(stderr, "[host] window: %s\n", SDL_GetError());
            return;
        }
        std::fprintf(stderr, "[host] SDL %d.%d.%d, window only\n", SDL_VERSIONNUM_MAJOR(SDL_GetVersion()),
                     SDL_VERSIONNUM_MINOR(SDL_GetVersion()), SDL_VERSIONNUM_MICRO(SDL_GetVersion()));
        pollEvents();
        return;
    }
#ifdef _WIN32 
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");
#endif
    if (!SDL_CreateWindowAndRenderer(title ? title : "", width, height, flags, &s_host.window, &s_host.renderer))
    {
        std::fprintf(stderr, "[host] window: %s\n", SDL_GetError());
        s_host.window = nullptr;
        s_host.renderer = nullptr;
        return;
    }
    // PS2_VSYNC=1: present at the refresh.
    const char *vsync = std::getenv("PS2_VSYNC");
    SDL_SetRenderVSync(s_host.renderer, vsync && std::strcmp(vsync, "1") == 0 ? 1 : 0);
    std::fprintf(stderr, "[host] SDL %d.%d.%d, renderer %s\n", SDL_VERSIONNUM_MAJOR(SDL_GetVersion()),

                 SDL_VERSIONNUM_MINOR(SDL_GetVersion()), SDL_VERSIONNUM_MICRO(SDL_GetVersion()),
                 SDL_GetRendererName(s_host.renderer));
    pollEvents();
}

void CloseWindow()
{
    for (SDL_Gamepad *&pad : s_host.gamepads)
        if (pad)
        {
            SDL_CloseGamepad(pad);
            pad = nullptr;
        }
    copyGamepads(); 
    if (s_host.renderer)
        SDL_DestroyRenderer(s_host.renderer);
    if (s_host.window)
        SDL_DestroyWindow(s_host.window);
    s_host.renderer = nullptr;
    s_host.window = nullptr;
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
}

bool IsWindowReady()

{
    return s_host.window != nullptr;
}

bool WindowShouldClose()
{
    return s_host.closeRequested;
}

bool IsWindowFocused()
{
    return s_host.window && (SDL_GetWindowFlags(s_host.window) & SDL_WINDOW_INPUT_FOCUS) != 0;   
}

void *GetWindowHandle()
{
#ifdef _WIN32
    if (s_host.window)
        return SDL_GetPointerProperty(SDL_GetWindowProperties(s_host.window), SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                                      nullptr);
#endif
    return nullptr;

}

int GetScreenWidth()
{
    int w = 0, h = 0;
    if (s_host.renderer)
        SDL_GetCurrentRenderOutputSize(s_host.renderer, &w, &h);   
    else if (s_host.window)

        SDL_GetWindowSizeInPixels(s_host.window, &w, &h);
    return w;
} 

int GetScreenHeight()
{
    int w = 0, h = 0;
    if (s_host.renderer)
        SDL_GetCurrentRenderOutputSize(s_host.renderer, &w, &h);
    else if (s_host.window)
        SDL_GetWindowSizeInPixels(s_host.window, &w, &h);
    return h;
}

int GetCurrentMonitor()
{
    return 0 ;
}

int GetMonitorRefreshRate(int /*monitor*/)

{
    const SDL_DisplayMode *mode =
        s_host.window ? SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(s_host.window)) : nullptr;
    return mode && mode->refresh_rate > 0.0f ? int(std::lround(mode->refresh_rate)) : 60;
}

void SetTargetFPS(int fps)
{
    s_host.targetFps = std::max(0, fps);
    s_host.nextFrameNs = 0;
}

double GetTime()
{
    return double(SDL_GetTicksNS() - s_host.startNs) * 1e-9;
}

const char *GetApplicationDirectory()
{
    if (s_host.baseDirectory.empty())
        if (const char *base = SDL_GetBasePath())
            s_host.baseDirectory = base;
    return s_host.baseDirectory.c_str();
}

void DisableCursor()
{
    if (s_host.window)
        SDL_SetWindowRelativeMouseMode(s_host.window, true);
}

void EnableCursor()   
 {
    if (s_host.window)
        SDL_SetWindowRelativeMouseMode(s_host.window, false);
}

void BeginDrawing()
{
}

void EndDrawing() 
{
    if (s_host.renderer)
         SDL_RenderPresent(s_host.renderer); 
    if (s_host.targetFps > 0)
    {
        const Uint64 period = 1000000000ull / Uint64(s_host.targetFps);
        const Uint64 now = SDL_GetTicksNS();
        if (s_host.nextFrameNs == 0 || now > s_host.nextFrameNs + period)
            s_host.nextFrameNs = now; // first frame, or far behind: no catch-up burst
        else if (now < s_host.nextFrameNs)
            SDL_DelayPrecise(s_host.nextFrameNs - now);
        s_host.nextFrameNs += period;
    }
    pollEvents();
}

void ClearBackground(Color color)
{
    if (!s_host.renderer)
        return;

    SDL_SetRenderDrawColor(s_host.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(s_host.renderer);
}

void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 /*origin*/, float /*rotation*/,
                    Color tint)
 {
    auto *tex = static_cast<SDL_Texture *>(texture.handle);
    if (!s_host.renderer || !tex)
        return;
    SDL_SetTextureColorMod(tex, tint.r, tint.g, tint.b);
    SDL_SetTextureAlphaMod(tex, tint.a) ;
    const SDL_FRect src{source.x, source.y, source.width, source.height};
    const SDL_FRect dst{dest.x, dest.y, dest.width, dest.height};
    SDL_RenderTexture(s_host.renderer, tex, &src, &dst);
}

void DrawRectangle(int x, int y, int width, int height, Color color)
{   
    if (!s_host.renderer)
        return;
    setDrawColor(color);
    const SDL_FRect rect{float(x), float(y), float(width), float(height)};
    SDL_RenderFillRect(s_host.renderer, &rect);
}

void DrawText(const char *text, int x, int y, int fontSize, Color color)

{
    if (!s_host.renderer || !text)
        return;
    const int scale = textScale(fontSize);
    setDrawColor(color);
    SDL_SetRenderScale(s_host.renderer, float(scale), float(scale));

    float lineY = float(y) / float(scale);
    for (const char *line = text; *line;)
    {   
        const char *end = std::strchr(line, '\n');
        const std::string part(line, end ? size_t(end - line) : std::strlen(line));   
        SDL_RenderDebugText(s_host.renderer, float(x) / float(scale), lineY, part.c_str()); 
        lineY += float(SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE + 2);
        if (!end)
            break;
        line = end + 1;
    }
    SDL_SetRenderScale(s_host.renderer, 1.0f, 1.0f);
}

int MeasureText(const char *text, int fontSize)
{
    if (!text)
        return 0;  

    size_t longest = 0, current = 0;
    for (const char *p = text; *p; ++p)
        if (*p == '\n')
            current = 0 ;

        else
            longest = std::max(longest, ++current);
    return int(longest) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * textScale(fontSize);
}

Image GenImageColor(int width, int height, Color color)
{
    Image image{nullptr, width, height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    auto *pixels = static_cast<Color *>(std::malloc(size_t(width) * size_t(height) * sizeof(Color)));
    if (pixels)
        std::fill(pixels, pixels + size_t(width) * size_t(height), color); 

    image.data = pixels; 

    return image;
}

void UnloadImage(Image image)

{
    std::free(image.data);
}

Texture2D LoadTextureFromImage(Image image)

{
    Texture2D texture{nullptr, image.width, image.height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
    if (!s_host.renderer)
        return texture;
    // ABGR8888: bytes R, G, B, A in memory.
    SDL_Texture *tex = SDL_CreateTexture(s_host.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
                                         image.width, image.height);
    if (!tex)
        return texture;
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    if (image.data)
        SDL_UpdateTexture(tex, nullptr, image.data, image.width * 4);
    texture.handle = tex;
    return texture;
}

void UnloadTexture(Texture2D texture)
{
    if (texture.handle)
        SDL_DestroyTexture(static_cast<SDL_Texture *>(texture.handle));
}

void UpdateTexture(Texture2D texture, const void *pixels)
{  
    if (texture.handle && pixels)
        SDL_UpdateTexture(static_cast<SDL_Texture *>(texture.handle), nullptr, pixels, texture.width * 4);

}

void SetTextureFilter(Texture2D texture, int filter)
{
    if (texture.handle)
        SDL_SetTextureScaleMode(static_cast<SDL_Texture *>(texture.handle),
                                filter == TEXTURE_FILTER_POINT ? SDL_SCALEMODE_NEAREST : SDL_SCALEMODE_LINEAR);
}

bool IsKeyDown(int key)
{

    return key > 0 && key < SDL_SCANCODE_COUNT && !s_uiKeyboard.load(std::memory_order_relaxed) &&
           s_keyDown[size_t(key)].load(std::memory_order_relaxed);
 }

bool IsKeyPressed(int key)  
{

    return key > 0 && key < SDL_SCANCODE_COUNT && s_host.pressed[size_t(key)]; 
}

bool IsGamepadAvailable(int gamepad)
{
    return gamepad >= 0 && gamepad < kMaxGamepads && s_gamepadState[gamepad].available.load(std::memory_order_acquire);
}

bool IsGamepadButtonDown(int gamepad, int button)
{
    return gamepad >= 0 && gamepad < kMaxGamepads && button > 0 && button < 32 &&
           (s_gamepadState[gamepad].buttons.load(std::memory_order_relaxed) >> button & 1u) != 0; 
}

float GetGamepadAxisMovement(int gamepad, int axis)
{
    if (gamepad < 0 || gamepad >= kMaxGamepads || axis < 0 || axis > GAMEPAD_AXIS_RIGHT_TRIGGER ||
        !IsGamepadAvailable(gamepad))

        return axis >= GAMEPAD_AXIS_LEFT_TRIGGER ? -1.0f : 0.0f;
    return s_gamepadState[gamepad].axes[axis].load(std::memory_order_relaxed);
}

bool IsMouseButtonDown(int button)
{
    return button >= 0 && button < 3 && !s_uiMouse.load(std::memory_order_relaxed) &&
           (s_mouseButtons.load(std::memory_order_relaxed) >> button & 1u) != 0;
}

Vector2 GetMouseDelta()
{
    return s_uiMouse.load(std::memory_order_relaxed) ? Vector2{0.0f, 0.0f} : s_host.mouseDelta;
}

void InitAudioDevice()
{
    s_host.audioReady = SDL_InitSubSystem(SDL_INIT_AUDIO);
    if (!s_host.audioReady)
        std::fprintf(stderr, "[host] audio: %s\n", SDL_GetError());
}

void CloseAudioDevice()
{ 
    if (s_host.audioReady)
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    s_host.audioReady = false;
}

bool IsAudioDeviceReady()
{
    return s_host.audioReady;
}

AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels)
{

    AudioStream result{nullptr, sampleRate, sampleSize, channels};
    if (!s_host.audioReady || sampleSize != 16 || channels != 2)
        return result;
    auto *data = new StreamData;
    const SDL_AudioSpec spec{SDL_AUDIO_S16, int(channels), int(sampleRate)};
    data->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audioCallback, data);
    if (!data->stream)
    {
        std::fprintf(stderr, "[host] audio stream: %s\n", SDL_GetError());
        delete data;
        return result;
    }
    result.handle = data;
    return result;
}

void SetAudioStreamCallback(AudioStream stream, AudioCallback callback)
{
    if (auto *data = static_cast<StreamData *>(stream.handle))
        data->callback.store(callback, std::memory_order_release);
}

void PlayAudioStream(AudioStream stream)
{
    if (auto *data = static_cast<StreamData *>(stream.handle))
        SDL_ResumeAudioStreamDevice(data->stream);
}

void StopAudioStream(AudioStream stream)

{
    if (auto *data = static_cast<StreamData *>(stream.handle))
         SDL_PauseAudioStreamDevice(data->stream);
}

void UnloadAudioStream(AudioStream stream)
{
    if (auto *data = static_cast<StreamData *>(stream.handle))
    {
        SDL_DestroyAudioStream(data->stream); // also closes its device
        delete data;
    }
}

Wave LoadWaveFromMemory(const char * /*fileType*/, const unsigned char *fileData, int dataSize)

{
    Wave wave{};
    SDL_AudioSpec spec{};
     Uint8 *pcm = nullptr;
    Uint32 bytes = 0;
    if (!fileData || dataSize <= 0 ||
        !SDL_LoadWAV_IO(SDL_IOFromConstMem(fileData, size_t(dataSize)), true, &spec, &pcm, &bytes))
        return wave;
    wave.frameCount = bytes / unsigned(SDL_AUDIO_FRAMESIZE(spec));
    wave.sampleRate = unsigned(spec.freq);
    wave.sampleSize = unsigned(SDL_AUDIO_BITSIZE(spec.format));
    wave.channels = unsigned(spec.channels);
    wave.data = pcm;
    return wave;
}

void UnloadWave(Wave wave)
 {
    SDL_free(wave.data);
}

Sound LoadSoundFromWave(Wave wave)
{

    Sound sound{{nullptr, wave.sampleRate, wave.sampleSize, wave.channels}, wave.frameCount};
    if (!s_host.audioReady || !wave.data || wave.frameCount == 0)
        return sound;
    const SDL_AudioFormat format = wave.sampleSize == 8    ? SDL_AUDIO_U8
                                   : wave.sampleSize == 32 ? SDL_AUDIO_F32
                                                           : SDL_AUDIO_S16;
    const SDL_AudioSpec spec{format, int(wave.channels), int(wave.sampleRate)};
     auto *data = new SoundData;
    data->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr); 

    if (!data->stream)
    {
        std::fprintf(stderr, "[host] sound stream: %s\n", SDL_GetError());
        delete data;
        return sound;
    }
    const auto *pcm = static_cast<const Uint8 *>(wave.data);
    data->pcm.assign(pcm, pcm + size_t(wave.frameCount) * size_t(SDL_AUDIO_FRAMESIZE(spec)));

    sound.stream.handle = data;
    return sound;
}

void UnloadSound(Sound sound)
{
    if (SoundData *data = soundData(sound))
     {
         SDL_DestroyAudioStream(data->stream);
        delete data;
    }
}

void PlaySound(Sound sound)
{
     if (SoundData *data = soundData(sound))
    {
        SDL_ClearAudioStream(data->stream);
        SDL_PutAudioStreamData(data->stream, data->pcm.data(), int(data->pcm.size()));
        SDL_FlushAudioStream(data->stream);
        SDL_ResumeAudioStreamDevice(data->stream);
     }

}

void StopSound(Sound sound)
{
    if (SoundData *data = soundData(sound))
    {
        SDL_PauseAudioStreamDevice(data->stream);
        SDL_ClearAudioStream(data->stream);
    }
 }

bool IsSoundPlaying(Sound sound)
{
    const SoundData *data = soundData(sound);
    return data && !SDL_AudioStreamDevicePaused(data->stream) && SDL_GetAudioStreamQueued(data->stream) > 0;
}

void SetSoundVolume(Sound sound, float volume)
{
     if (SoundData *data = soundData(sound))
        SDL_SetAudioStreamGain(data->stream, std::max(0.0f, volume));
 }

void SetSoundPitch(Sound sound, float pitch)  
{
    if (SoundData *data = soundData(sound))
        SDL_SetAudioStreamFrequencyRatio(data->stream, std::clamp(pitch, 0.01f, 100.0f));
}

void ps2HostSetWindowOnly(bool windowOnly)   
{
    s_host.windowOnly = windowOnly;
}

SDL_Window *ps2HostWindow()  
{
    return s_host.window;  
}

void ps2HostPollEvents()
{
    pollEvents();
}

SDL_Renderer *ps2HostRenderer()
{
    return s_host.renderer;
}

void ps2HostSetEventHook(void (*hook)(const SDL_Event *event))
{
    s_host.eventHook = hook;
}

void ps2HostSetUiCapture(bool keyboard, bool mouse)
{
    s_uiKeyboard.store(keyboard, std::memory_order_relaxed);
    s_uiMouse.store(mouse, std::memory_order_relaxed);
}

bool ps2HostUiWantsKeyboard()
{
    return s_uiKeyboard.load(std::memory_order_relaxed);
}

void ps2HostSetRumble(float small, float big)
{
    const uint32_t high = uint32_t(std::lround(std::clamp(small, 0.0f, 1.0f) * 65535.0f));
    const uint32_t low = uint32_t(std::lround(std::clamp(big, 0.0f, 1.0f) * 65535.0f));
    s_rumble.store(low | (high << 16), std::memory_order_relaxed);
}
