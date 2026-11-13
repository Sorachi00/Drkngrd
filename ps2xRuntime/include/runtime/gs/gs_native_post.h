#pragma once
#include "runtime/gs/render_cmd.h"
#include <memory>

namespace GSNativePost

{
    void world(const rdraw::NativeContext &c, const float worldToWindow[4][4], int priority, double fogFar) ;

    std::unique_ptr<RenderCmd> makeDraw();
}
