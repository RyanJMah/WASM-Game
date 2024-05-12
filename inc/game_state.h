#pragma once

#include <SDL2/SDL.h>
#include "assets.h"

typedef struct
{
    SDL_Window*   p_window;
    SDL_Renderer* p_renderer;

    uint32_t      window_h;
    uint32_t      window_w;

    CharAssets_t  char_assets;
} GameState_t;