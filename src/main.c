#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "macros.h"
#include "assets.h"
#include "game_state.h"

#ifdef WASM
#include <emscripten.h>
#endif

#ifndef WASM
    #define FRAME_RATE          ( 60 )
    #define FRAME_TIME_TICKS    ( 1000 / FRAME_RATE )

    static uint32_t g_quit = 0;
#endif

static GameState_t g_state =
{
    .window_h = 480,
    .window_w = 640,
};


static inline void _initial_game_state(void)
{
    g_state.curr_scale = 1;

    Character_Init(&g_state.character);

    g_state.character.p_texture = g_state.char_assets.named.p_down1;
}

void main_loop(void)
{
    int err_code = 0;

    SDL_Event e;
    if ( SDL_PollEvent(&e) )
    {
        switch (e.type)
        {
            case SDL_QUIT:
            {
            #ifdef WASM
                emscripten_cancel_main_loop();
            #else
                g_quit = 1;
            #endif

                break;
            }
        }
    }

    const uint8_t* key_state = SDL_GetKeyboardState(NULL);
    bool key_pressed = false;

    // Diagonal up+right
    if ( key_state[SDL_SCANCODE_W] && key_state[SDL_SCANCODE_D] )
    {
        if ( g_state.character.orientation != CHAR_FACING_RIGHT )
        {
            g_state.character.orientation = CHAR_FACING_RIGHT;
            g_state.character.p_texture   = g_state.char_assets.named.p_right1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x += g_state.character.velocity;
        g_state.character.y -= g_state.character.velocity;
        key_pressed = true;
    }

    // Diagonal up+left
    else if ( key_state[SDL_SCANCODE_W] && key_state[SDL_SCANCODE_A] )
    {
        if ( g_state.character.orientation != CHAR_FACING_LEFT )
        {
            g_state.character.orientation = CHAR_FACING_LEFT;
            g_state.character.p_texture   = g_state.char_assets.named.p_left1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x -= g_state.character.velocity;
        g_state.character.y -= g_state.character.velocity;
        key_pressed = true;
    }

    // Diagonal down+right
    else if ( key_state[SDL_SCANCODE_S] && key_state[SDL_SCANCODE_D] )
    {
        if ( g_state.character.orientation != CHAR_FACING_RIGHT )
        {
            g_state.character.orientation = CHAR_FACING_RIGHT;
            g_state.character.p_texture   = g_state.char_assets.named.p_right1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x += g_state.character.velocity;
        g_state.character.y += g_state.character.velocity;
        key_pressed = true;
    }

    // Diagonal down+left
    else if ( key_state[SDL_SCANCODE_S] && key_state[SDL_SCANCODE_A] )
    {
        if ( g_state.character.orientation != CHAR_FACING_LEFT )
        {
            g_state.character.orientation = CHAR_FACING_LEFT;
            g_state.character.p_texture   = g_state.char_assets.named.p_left1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x -= g_state.character.velocity;
        g_state.character.y += g_state.character.velocity;
        key_pressed = true;
    }

    // Up
    else if ( key_state[SDL_SCANCODE_W] )
    {
        if ( g_state.character.orientation != CHAR_FACING_UP )
        {
            g_state.character.orientation = CHAR_FACING_UP;
            g_state.character.p_texture   = g_state.char_assets.named.p_up1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.y -= g_state.character.velocity;
        key_pressed = true;
    }

    // Down
    else if ( key_state[SDL_SCANCODE_S] )
    {
        if ( g_state.character.orientation != CHAR_FACING_DOWN )
        {
            g_state.character.orientation = CHAR_FACING_DOWN;
            g_state.character.p_texture   = g_state.char_assets.named.p_down1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.y += g_state.character.velocity;
        key_pressed = true;
    }

    // Left
    else if ( key_state[SDL_SCANCODE_A] )
    {
        if ( g_state.character.orientation != CHAR_FACING_LEFT )
        {
            g_state.character.orientation = CHAR_FACING_LEFT;
            g_state.character.p_texture   = g_state.char_assets.named.p_left1;
        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x -= g_state.character.velocity;
        key_pressed = true;
    }

    // Right
    else if ( key_state[SDL_SCANCODE_D] )
    {
        if ( g_state.character.orientation != CHAR_FACING_RIGHT )
        {
            g_state.character.orientation = CHAR_FACING_RIGHT;
            g_state.character.p_texture   = g_state.char_assets.named.p_right1;

        }

        Character_CycleTexture(&g_state.character, &g_state.char_assets);

        g_state.character.x += g_state.character.velocity;
        key_pressed = true;
    }

    if ( !key_pressed )
    {
        Character_SetIdleTexture(&g_state.character, &g_state.char_assets);
    }

    // Clear the entire screen to our selected color
    err_code = SDL_RenderClear(g_state.p_renderer);
    require_noerr(err_code, exit);

    // Render the character
    err_code = render_character( &g_state.character, g_state.p_renderer );
    require_noerr(err_code, exit);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, white contents of the g_game_state.p_window.
    SDL_RenderPresent(g_state.p_renderer);

exit:
    if ( err_code != 0 )
    {
        printf( "Error: %s\n", SDL_GetError() );
    }
}


int main(int argc, char* argv[])
{
    int err_code = 0;

    // Initialize SDL2
    err_code = SDL_Init(SDL_INIT_VIDEO);
    require_noerr(err_code, exit);

    // Initialize SDL_image with PNG support
    err_code = IMG_Init(IMG_INIT_PNG);
    require(err_code & IMG_INIT_PNG, exit);

    // Create an application g_game_state.p_window with the following settings:
    g_state.p_window = SDL_CreateWindow( "Hello World",           // g_game_state.p_window title
                                         SDL_WINDOWPOS_UNDEFINED, // initial x position
                                         SDL_WINDOWPOS_UNDEFINED, // initial y position
                                         g_state.window_w,   // width, in pixels
                                         g_state.window_h,   // height, in pixels
                                         0 );                     // flags
    require( g_state.p_window != NULL, exit );

    g_state.p_renderer = SDL_CreateRenderer(g_state.p_window, -1, SDL_RENDERER_ACCELERATED);
    require( g_state.p_renderer != NULL, exit );

    // Set the draw color to black
    err_code = SDL_SetRenderDrawColor(g_state.p_renderer, 0, 0, 0, 255);
    require_noerr(err_code, exit);

    // Load assets
    err_code = CharAssets_Load(g_state.p_renderer, &g_state.char_assets);
    require_noerr(err_code, exit);

    // Set the initial game state
    _initial_game_state();

#ifdef WASM
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while ( !g_quit )
    {
        uint32_t start = SDL_GetTicks();
        main_loop();
        uint32_t end = SDL_GetTicks();

        uint32_t frame_time = end - start;

        if ( frame_time < FRAME_TIME_TICKS )
        {
            SDL_Delay(FRAME_TIME_TICKS - frame_time);
        }
    }
#endif


exit:
    SDL_DestroyRenderer(g_state.p_renderer);
    SDL_DestroyWindow(g_state.p_window);

    free_textures( g_state.char_assets.texture_arr,
                   ARRAY_LEN(g_state.char_assets.texture_arr) );

    printf( "Error: %s\n", SDL_GetError() );
    SDL_Quit();

    return 0;
}
