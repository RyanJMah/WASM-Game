#include "assets.h"
#include "macros.h"
#include "err_codes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int load_character_assets( SDL_Renderer* p_renderer,
                           SDL_Texture** out_textures,
                           uint32_t*     out_num_textures )
{
    static const char* asset_paths_fmt[] =
    {
        PATH_CONCAT2(ASSETS_PATH, "character/up1.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/up2.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/up3.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/up4.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/down1.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/down2.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/down3.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/down4.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/left1.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/left2.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/left3.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/left4.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/right1.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/right2.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/right3.png"),
        PATH_CONCAT2(ASSETS_PATH, "character/right4.png"),
    };

    int err_code = 0;

    const uint32_t num_assets = ARRAY_LEN(asset_paths_fmt);

    out_textures = (SDL_Texture**)malloc( num_assets * sizeof(SDL_Texture*) );
    require_action( out_textures != NULL,
                    exit,
                    err_code=ERR_ALLOC );

    for (uint32_t i = 0; i < num_assets; i++)
    {
        out_textures[i] = IMG_LoadTexture(p_renderer, asset_paths_fmt[i]);
        require_action( out_textures[i] != NULL,
                        exit,
                        err_code = -1 );
    }

    *out_num_textures = num_assets;

exit:
    return err_code;
}

void free_character_assets( SDL_Texture** textures,
                            uint32_t      num_textures )
{
    for (uint32_t i = 0; i < num_textures; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }

    free(textures);
}

