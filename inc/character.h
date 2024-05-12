#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

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

    CharOrientation_t orientation;

    uint32_t     velocity;
    SDL_Texture* p_texture;
} Character_t;

int render_character(Character_t* character, SDL_Renderer* p_renderer);
