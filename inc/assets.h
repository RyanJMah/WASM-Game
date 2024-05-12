#pragma once

#include <SDL2/SDL.h>

int load_character_assets( SDL_Renderer* p_renderer,
                           SDL_Texture** out_textures,
                           uint32_t*     out_num_textures );

void free_character_assets( SDL_Texture** textures,
                            uint32_t      num_textures );
