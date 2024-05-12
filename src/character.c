#include "macros.h"
#include "character.h"

void Character_Init(Character_t* character)
{
    character->x = 0;
    character->y = 0;
    character->velocity = 5;
    character->orientation = CHAR_FACING_DOWN;

    character->p_texture = NULL;
    character->curr_texture_index = 0;
}

void Character_CycleTexture(Character_t* character, CharAssets_t* assets)
{
    SDL_Texture* p_texture1 = NULL;

    switch (character->orientation)
    {
        case CHAR_FACING_UP:
        {
            p_texture1 = assets->named.p_up1;
            break;
        }

        default:
        case CHAR_FACING_DOWN:
        {
            p_texture1 = assets->named.p_down1;
            break;
        }

        case CHAR_FACING_LEFT:
        {
            p_texture1 = assets->named.p_left1;
            break;
        }

        case CHAR_FACING_RIGHT:
        {
            p_texture1 = assets->named.p_right1;
            break;
        }
    }

    /*
     * SDL_Texture is an opaque type for some reason, but I refuse to
     * hardcode the array offsets, so lets just do a linear search
     * for the index in the array (lol).
     */
    uint32_t curr_index_in_assets_arr = 0;

    for (uint32_t i = 0; i < ARRAY_LEN(assets->texture_arr); i++)
    {
        if (assets->texture_arr[i] == p_texture1)
        {
            curr_index_in_assets_arr = i;
            break;
        }
    }

    // Calculate the desired index by adding the current texture index
    uint32_t desired_index = curr_index_in_assets_arr + character->curr_texture_index;

    // Check if the desired index is within the bounds of the texture array
    if ( desired_index < ARRAY_LEN(assets->texture_arr) )
    {
        character->p_texture = assets->texture_arr[desired_index];
    }
    else
    {
        // Handle error: index out of bounds, could log this or default to a safe value
        DEBUG_LOG("Index out of bounds, defaulting to safe value..\r\n");
        character->p_texture = assets->named.p_down1;
    }

    // Update curr_texture_index to cycle through the next textures
    character->curr_texture_index = (character->curr_texture_index + 1) % 4;
}

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
