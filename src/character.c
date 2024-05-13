#include "macros.h"
#include "constants.h"
#include "character.h"

static inline SDL_Texture** _get_base_texture(Character_t* character, CharAssets_t* assets)
{
    switch (character->orientation)
    {
        case CHAR_FACING_UP:
        {
            return &assets->named.p_up1;
        }

        default:
        case CHAR_FACING_DOWN:
        {
            return &assets->named.p_down1;
        }

        case CHAR_FACING_LEFT:
        {
            return &assets->named.p_left1;
        }

        case CHAR_FACING_RIGHT:
        {
            return &assets->named.p_right1;
        }
    }
}


void Character_Init(Character_t* character)
{
    character->x = 0;
    character->y = 0;
    character->velocity = CHARACTER_VELOCITY;
    character->orientation = CHAR_FACING_DOWN;

    character->p_texture = NULL;
    character->curr_texture_index = 0;

    // Initialize to same val minus one, so the walking animation starts immediately
    character->texture_swap_rate    = CHARACTER_TEXTURE_SWAP_RATE;
    character->texture_swap_counter = character->texture_swap_rate - 1;
}

void Character_CycleTexture(Character_t* character, CharAssets_t* assets)
{
    character->texture_swap_counter++;

    if (character->texture_swap_counter < character->texture_swap_rate)
    {
        return;
    }

    character->texture_swap_counter = 0;

    SDL_Texture** p_base_texture = _get_base_texture(character, assets);

    // Get the current index of the texture in the assets array
    int32_t curr_index_in_assets_arr = p_base_texture - &assets->texture_arr[0];

    // Calculate the desired index by adding the current texture index
    uint32_t desired_index = curr_index_in_assets_arr + character->curr_texture_index;

    // Check if the desired index is within the bounds of the texture array
    if ( desired_index < ARRAY_LEN(assets->texture_arr) )
    {
        character->p_texture = &assets->texture_arr[desired_index];
    }
    else
    {
        // Handle error: index out of bounds, could log this or default to a safe value
        printf("Error: Texture index out of bounds: %d, %d\r\n", curr_index_in_assets_arr, desired_index);
        character->p_texture = &assets->named.p_down1;
    }

    // Update curr_texture_index to cycle through the next textures
    character->curr_texture_index = (character->curr_texture_index + 1) % 4;
}

void Character_SetIdleTexture(Character_t* character, CharAssets_t* assets)
{
    character->p_texture = _get_base_texture(character, assets);
}

int render_character( Character_t* character,
                      SDL_Renderer* p_renderer,
                      float* p_scale )
{
    int err_code = 0;

    int texWidth, texHeight;

    // Get the width and height of the texture
    err_code = SDL_QueryTexture(*character->p_texture, NULL, NULL, &texWidth, &texHeight);
    require_noerr(err_code, exit);

    texHeight *= (*p_scale);
    texWidth  *= (*p_scale);

    SDL_Rect dstRect;
    dstRect.x = character->x;
    dstRect.y = character->y;
    dstRect.w = texWidth;
    dstRect.h = texHeight;

    err_code = SDL_RenderCopy( p_renderer,
                               *character->p_texture,
                               NULL,
                               &dstRect );  // Draw the image
    require_noerr(err_code, exit);

exit:
    return err_code;
}
