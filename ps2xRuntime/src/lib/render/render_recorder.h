#pragma once
#include <memory>

class GS;

std::unique_ptr<GS> makeRenderRecorder();
