#pragma once

#include <SDL2/SDL.h>

#include "macros.h"
#include "err_codes.h"

#define LOAD_TEXTURE( p_renderer_, path_ )    IMG_LoadTexture(p_renderer_, PATH_CONCAT2(ASSETS_PATH, path_))

typedef union
{
    struct
    {
        SDL_Texture* p_up1;
        SDL_Texture* p_up2;
        SDL_Texture* p_up3;
        SDL_Texture* p_up4;

        SDL_Texture* p_down1;
        SDL_Texture* p_down2;
        SDL_Texture* p_down3;
        SDL_Texture* p_down4;

        SDL_Texture* p_left1;
        SDL_Texture* p_left2;
        SDL_Texture* p_left3;
        SDL_Texture* p_left4;

        SDL_Texture* p_right1;
        SDL_Texture* p_right2;
        SDL_Texture* p_right3;
        SDL_Texture* p_right4;
    } named;

    SDL_Texture* texture_arr[16];
} CharAssets_t;

err_code_t CharAssets_Load( SDL_Renderer* p_renderer,
                            CharAssets_t* out_assets );

void free_textures( SDL_Texture** textures,
                    uint32_t      num_textures );
