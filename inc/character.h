#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#include "assets.h"

typedef enum
{
    CHAR_FACING_UP,
    CHAR_FACING_DOWN,
    CHAR_FACING_LEFT,
    CHAR_FACING_RIGHT
} CharOrientation_t;

typedef struct
{
    double x;
    double y;
    double velocity;

    CharOrientation_t orientation;

    SDL_Texture** p_texture;
    uint32_t      curr_texture_index;

    uint32_t texture_swap_counter;
    uint32_t texture_swap_rate;
} Character_t;

void Character_Init(Character_t* character);

void Character_CycleTexture(Character_t* character, CharAssets_t* assets);
void Character_SetIdleTexture(Character_t* character, CharAssets_t* assets);

// Scale can be NULL
int render_character(Character_t* character, SDL_Renderer* p_renderer, float* p_scale);
