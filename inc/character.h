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
    uint32_t x;
    uint32_t y;
    uint32_t velocity;

    CharOrientation_t orientation;

    SDL_Texture* p_texture;
    uint32_t     curr_texture_index;
} Character_t;

void Character_Init(Character_t* character);

void Character_CycleTexture(Character_t* character, CharAssets_t* assets);
void Character_SetIdleTexture(Character_t* character, CharAssets_t* assets);

int render_character(Character_t* character, SDL_Renderer* p_renderer);
