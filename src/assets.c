#include "assets.h"
#include "macros.h"
#include "err_codes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void free_textures( SDL_Texture** textures,
                    uint32_t      num_textures )
{
    for (uint32_t i = 0; i < num_textures; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }

    free(textures);
}

err_code_t CharAssets_Load( SDL_Renderer* p_renderer,
                            CharAssets_t* out_assets )
{
    err_code_t err_code = ERR_OK;

    out_assets->named.p_up1 = LOAD_TEXTURE(p_renderer, "character/up1.png");
    out_assets->named.p_up2 = LOAD_TEXTURE(p_renderer, "character/up2.png");
    out_assets->named.p_up3 = LOAD_TEXTURE(p_renderer, "character/up3.png");
    out_assets->named.p_up4 = LOAD_TEXTURE(p_renderer, "character/up4.png");

    out_assets->named.p_down1 = LOAD_TEXTURE(p_renderer, "character/down1.png");
    out_assets->named.p_down2 = LOAD_TEXTURE(p_renderer, "character/down2.png");
    out_assets->named.p_down3 = LOAD_TEXTURE(p_renderer, "character/down3.png");
    out_assets->named.p_down4 = LOAD_TEXTURE(p_renderer, "character/down4.png");

    out_assets->named.p_left1 = LOAD_TEXTURE(p_renderer, "character/left1.png");
    out_assets->named.p_left2 = LOAD_TEXTURE(p_renderer, "character/left2.png");
    out_assets->named.p_left3 = LOAD_TEXTURE(p_renderer, "character/left3.png");
    out_assets->named.p_left4 = LOAD_TEXTURE(p_renderer, "character/left4.png");

    out_assets->named.p_right1 = LOAD_TEXTURE(p_renderer, "character/right1.png");
    out_assets->named.p_right2 = LOAD_TEXTURE(p_renderer, "character/right2.png");
    out_assets->named.p_right3 = LOAD_TEXTURE(p_renderer, "character/right3.png");
    out_assets->named.p_right4 = LOAD_TEXTURE(p_renderer, "character/right4.png");


    // Check if any of the textures failed to load
    for (uint32_t i = 0; i < ARRAY_LEN(out_assets->texture_arr); i++)
    {
        require_action( out_assets->texture_arr[i] != NULL,
                        exit,
                        err_code = ERR_ALLOC );
    }

    printf("Successfully loaded character assets..\r\n");

exit:
    return err_code;
}
