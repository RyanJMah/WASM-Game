#include "macros.h"
#include "character.h"

int render_character(Character_t* character, SDL_Renderer* p_renderer)
{
    int err_code = 0;

    int texWidth, texHeight;

    // Get the width and height of the texture
    err_code = SDL_QueryTexture(character->p_texture, NULL, NULL, &texWidth, &texHeight);
    require_noerr(err_code, exit);

    texHeight *= 2;
    texWidth  *= 2;

    SDL_Rect dstRect;
    dstRect.x = character->x;
    dstRect.y = character->y;
    dstRect.w = texWidth;
    dstRect.h = texHeight;

    err_code = SDL_RenderCopy( p_renderer,
                               character->p_texture,
                               NULL,
                               &dstRect );  // Draw the image
    require_noerr(err_code, exit);

exit:
    return err_code;
}
