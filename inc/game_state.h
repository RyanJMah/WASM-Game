#pragma once

#include <SDL2/SDL.h>
#include "assets.h"

typedef struct
{
    SDL_Window*   p_window;
    SDL_Renderer* p_renderer;

    CharAssets_t char_assets;

    uint32_t window_h;
    uint32_t window_w;

    uint32_t curr_scale;

    uint32_t char_x;
    uint32_t char_y;

    uint32_t char_velocity;
    SDL_Texture* p_char_texture;
    
} GameState_t;