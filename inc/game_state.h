#pragma once

#include <SDL2/SDL.h>
#include "assets.h"
#include "character.h"

typedef struct
{
    SDL_Window*   p_window;
    SDL_Renderer* p_renderer;

    CharAssets_t char_assets;

    uint32_t window_h;
    uint32_t window_w;

    uint32_t curr_scale;

    Character_t character;
} GameState_t;