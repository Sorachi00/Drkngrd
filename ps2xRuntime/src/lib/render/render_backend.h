
#pragma once
#include <memory>

class GSRasterBackend;
class RenderCmd;
struct RenderState;

std::unique_ptr<GSRasterBackend> makeRenderBackend();

void renderRunCommand(GSRasterBackend &backend, RenderCmd &cmd, const RenderState &state);
