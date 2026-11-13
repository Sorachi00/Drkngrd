#pragma once

#include <cstdint>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Texture2D;

namespace GSWindowPresent
{
    void setWindow(void *hwnd); 
    // The window's client size in pixels (0: minimized, nothing is drawn).
    void setClientSize(uint32_t width, uint32_t height);
    void setAspect(float aspect);
    void setVsync( bool on);
    bool active();
    uint64_t presentedFrames();

    void setUiRenderer(void (*draw)(void *user), void *user );
    void uiLock();
    void uiUnlock();
    struct UiLock
    {
        UiLock() { uiLock(); }
        ~UiLock() { uiUnlock(); }
        UiLock(const UiLock &) = delete;
        UiLock &operator=(const UiLock &) = delete;
    };
    ID3D11Device *device();
    ID3D11DeviceContext *uiContext();   

    void setPresentedCallback(void (*callback)(int64_t presentNs, uint64_t frame));

    void setDevice(ID3D11Device *device);
    void present(ID3D11DeviceContext *ctx, ID3D11Texture2D *image, uint32_t width, uint32_t height);

    void shutdown();  
} 
