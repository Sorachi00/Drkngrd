#pragma once


#include <cstdint>

struct SDL_Renderer;
struct SDL_Window;
union SDL_Event;

struct Vector2
{
    float x, y;
};

struct Rectangle

 {
    float x, y, width, height;
 };

struct Color
{
    unsigned char r, g, b, a;
};

// RGBA8 pixels (PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 only).
struct Image 
{
    void *data;
    int width;
    int height;

    int mipmaps;
    int format;
};

// handle: the SDL_Texture.
struct Texture2D   
{
    void *handle;
    int width;
    int height ;
    int mipmaps;
    int format;
};

// handle: the SDL_AudioStream.
struct AudioStream
{
    void *handle;
    unsigned int sampleRate;
    unsigned int sampleSize;
    unsigned int channels;
};   

using AudioCallback = void (*)(void *bufferData, unsigned int frames);

// data: SDL_LoadWAV PCM (SDL_free).
struct Wave
{

    unsigned int frameCount;
    unsigned int sampleRate;
    unsigned int sampleSize;
     unsigned int channels;   
    void *data ;
};

// stream.handle: the sound's own SDL_AudioStream and PCM copy.
struct Sound
{
    AudioStream stream;
    unsigned int frameCount;
} ;

inline constexpr Color BLACK{0, 0, 0, 255};

inline constexpr Color WHITE{255, 255, 255, 255};
inline constexpr Color BLANK{0, 0, 0, 0};
inline constexpr Color MAGENTA{255, 0, 255, 255};
inline constexpr Color GREEN{0, 228, 48, 255};
inline constexpr Color YELLOW{253, 249, 0, 255};  

enum ConfigFlags
{
    FLAG_WINDOW_RESIZABLE = 0x00000004,
    FLAG_WINDOW_ALWAYS_RUN = 0x00000100,
};

enum PixelFormat
{
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = 7,
};

enum TextureFilter
{
    TEXTURE_FILTER_POINT = 0,
    TEXTURE_FILTER_BILINEAR = 1,
} ;

enum KeyboardKey
{
    KEY_NULL = 0,
    KEY_A = 4,
    KEY_B = 5,   
    KEY_C = 6,
    KEY_D = 7,
    KEY_E = 8,
    KEY_F = 9,
    KEY_G = 10,
    KEY_H = 11,
    KEY_I = 12,
    KEY_J = 13,
    KEY_K = 14,
    KEY_L = 15,
    KEY_M = 16,
    KEY_N = 17,
    KEY_O = 18,
    KEY_P = 19,
    KEY_Q = 20,
    KEY_R = 21,
    KEY_S = 22,
    KEY_T = 23,
    KEY_U = 24,
    KEY_V = 25,
    KEY_W = 26, 
    KEY_X = 27,
     KEY_Y = 28,
    KEY_Z = 29,
    KEY_ONE = 30,
    KEY_TWO = 31,

    KEY_THREE = 32,
    KEY_ENTER = 40,
    KEY_ESCAPE =  41,  
    KEY_BACKSPACE = 42,
    KEY_TAB = 43,
    KEY_SPACE = 44,
    KEY_F1 = 58,
    KEY_F2 = 59,
    KEY_F9 = 66,  
    KEY_F10 = 67,
    KEY_RIGHT = 79,
    KEY_LEFT = 80,
    KEY_DOWN = 81,
    KEY_UP = 82,
    KEY_KP_ENTER = 88,
    KEY_KP_1 = 89,
    KEY_KP_2 = 90,
    KEY_KP_4 = 92,

    KEY_KP_6 = 94,
    KEY_KP_7 = 95,
    KEY_KP_8 = 96,
    KEY_KP_9 = 97,
    KEY_KP_0 = 98,
    KEY_LEFT_CONTROL = 224,
    KEY_LEFT_SHIFT = 225,
    KEY_LEFT_ALT = 226,
     KEY_RIGHT_CONTROL = 228,
    KEY_RIGHT_SHIFT = 229,
};

enum MouseButton
{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2,
};

enum GamepadButton
{
    GAMEPAD_BUTTON_UNKNOWN = 0,
    GAMEPAD_BUTTON_LEFT_FACE_UP,
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT, 
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,
    GAMEPAD_BUTTON_RIGHT_FACE_UP,
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,   
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,   
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2,
    GAMEPAD_BUTTON_MIDDLE_LEFT,
    GAMEPAD_BUTTON_MIDDLE,
    GAMEPAD_BUTTON_MIDDLE_RIGHT,
     GAMEPAD_BUTTON_LEFT_THUMB,
    GAMEPAD_BUTTON_RIGHT_THUMB,
};

enum GamepadAxis 
{
    GAMEPAD_AXIS_LEFT_X = 0,

    GAMEPAD_AXIS_LEFT_Y = 1,
    GAMEPAD_AXIS_RIGHT_X = 2,
    GAMEPAD_AXIS_RIGHT_Y = 3,
    GAMEPAD_AXIS_LEFT_TRIGGER =  4,   
    GAMEPAD_AXIS_RIGHT_TRIGGER = 5,
};

// Window and timing (window thread).
void SetConfigFlags(unsigned int flags);
void InitWindow(int width, int height, const char *title);
void CloseWindow();

bool IsWindowReady();
 bool WindowShouldClose();
bool IsWindowFocused();

void *GetWindowHandle(); // HWND on Windows
int GetScreenWidth();    // drawing area in pixels
int GetScreenHeight();
int GetCurrentMonitor();
int GetMonitorRefreshRate(int monitor); // the window's display
void SetTargetFPS(int fps);             // EndDrawing waits; 0: no limit
 double GetTime();
const char *GetApplicationDirectory();
void DisableCursor(); // relative mouse mode (GetMouseDelta)
void EnableCursor();

void BeginDrawing();
void EndDrawing();
void ClearBackground(Color color);
void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
void DrawRectangle(int x, int y, int width, int height, Color color);

void DrawText(const char *text, int x, int y, int fontSize, Color color);
int MeasureText(const char *text, int fontSize);

Image GenImageColor(int width, int height, Color color);
void UnloadImage(Image image);

Texture2D LoadTextureFromImage(Image image);
void UnloadTexture(Texture2D texture);
void UpdateTexture(Texture2D texture, const void *pixels);
void SetTextureFilter(Texture2D texture, int filter);

 // Input. Any thread: the window thread copies the state after each event read.
bool IsKeyDown(int key);
bool IsKeyPressed(int key); // window thread: pressed since the last frame  
bool IsGamepadAvailable(int gamepad);
bool IsGamepadButtonDown(int gamepad, int button);
float GetGamepadAxisMovement(int gamepad, int axis);
bool IsMouseButtonDown(int button);
Vector2 GetMouseDelta(); // window thread: movement in the last frame

// Audio.
void InitAudioDevice();
void CloseAudioDevice();
 bool IsAudioDeviceReady();
AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels);
void UnloadAudioStream(AudioStream stream);
void SetAudioStreamCallback(AudioStream stream, AudioCallback callback);
void PlayAudioStream(AudioStream stream) ;
void StopAudioStream(AudioStream stream);

// One-shot samples (PS2AudioBackend sample player): 16-bit WAV in memory.
Wave LoadWaveFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);
void UnloadWave(Wave wave);
Sound LoadSoundFromWave(Wave wave);
void UnloadSound(Sound sound);
void PlaySound(Sound sound);
void StopSound(Sound sound);
bool IsSoundPlaying(Sound sound);
void SetSoundVolume(Sound sound, float volume);
void SetSoundPitch(Sound sound, float pitch);

void ps2HostSetWindowOnly(bool windowOnly);
// SDL3 objects for the window thread (renderer null in window-only mode).
SDL_Window *ps2HostWindow();
SDL_Renderer *ps2HostRenderer();

void ps2HostPollEvents();
// Called with every SDL event the window reads (the debug UI's ImGui).
void ps2HostSetEventHook(void (*hook)(const SDL_Event *event));
void ps2HostSetUiCapture(bool keyboard, bool mouse);
bool ps2HostUiWantsKeyboard();
void ps2HostSetRumble(float small, float big);
