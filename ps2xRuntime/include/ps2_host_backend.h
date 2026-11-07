#pragma once

// Desktop: SDL3 (ps2_host_sdl3.h). Vita and Android: raylib.  

#if defined(PS2X_HOST_SDL3)
#include "ps2_host_sdl3.h"
#else
#include "raylib.h"
#endif
