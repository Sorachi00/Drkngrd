#pragma once

#include "runtime/gs/gs_backend.h"

#include <memory>

std::unique_ptr<GSRasterBackend> makeThreadedGsBackend(std::unique_ptr<GSRasterBackend> inner);
