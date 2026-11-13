#pragma once
// The native font's run on the render thread (exe; runtime/gs/gs_native_font.h).
#include "dk_render_abi.h"

#include "runtime/gs/gs_native_font.h"
#include "runtime/gs/render_data.h"

struct RenderFontHost 
{
    // The targets of context c (with depth: its Z buffer) bound; false: not drawn.
    virtual bool bind(const GSContext &c, bool depth) = 0;
    virtual void drawn(bool depthWritten) = 0;
    virtual bool texture(const GSTex0Reg &tex0, uint64_t clamp, const GSTexaReg &texa, const GSTexClutReg &texclut, DkNativeTexture &out) = 0;
    virtual void submit(const GSPrimitiveBatch &batch) = 0;
    virtual void transfer(const GSTransferCommand &command) = 0;
    virtual void upload(const uint8_t *data, uint32_t size) = 0;

  protected:
    ~RenderFontHost() = default;
};

void renderFont(RenderFontHost &host, const GSNativeFontBatch &batch, DkRes *font, const RenderState &env);
