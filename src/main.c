#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "macros.h"
#include "assets.h"
#include "game_state.h"

#ifdef WASM
#include <emscripten.h>
#endif

static GameState_t g_game_state =
{
    .window_h = 480,
    .window_w = 640,
};

#ifndef WASM
    #define FRAME_RATE          ( 60 )
    #define FRAME_TIME_TICKS    ( 1000 / FRAME_RATE )

    static uint32_t g_quit = 0;
#endif

void main_loop(void)
{
    int err_code = 0;

    SDL_Texture* p_texture = g_game_state.char_assets.named.p_down1;

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

            // case SDL_KEYDOWN:
            // {
            //     switch (e.key.keysym.sym)
            //     {
            //         // wasd
            //         case SDLK_w:
            //         {

            //         }
            //     }

            //     break;
            // }
        }
    }

    int texWidth, texHeight;

    // Get the width and height of the texture
    err_code = SDL_QueryTexture(p_texture, NULL, NULL, &texWidth, &texHeight);
    require_noerr(err_code, exit);

    texHeight *= 2;
    texWidth  *= 2;

    SDL_Rect dstRect;
    dstRect.x = (g_game_state.window_w - texWidth) / 2;     // Center the image horizontally
    dstRect.y = (g_game_state.window_h - texHeight) / 2;    // Center the image vertically
    dstRect.w = texWidth;                                   // Use the original image width
    dstRect.h = texHeight;                                  // Use the original image height

    err_code = SDL_RenderCopy(g_game_state.p_renderer, p_texture, NULL, &dstRect);  // Draw the image
    require_noerr(err_code, exit);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, white contents of the g_game_state.p_window.
    SDL_RenderPresent(g_game_state.p_renderer);

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
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_image with PNG support
    err_code = IMG_Init(IMG_INIT_PNG);
    require(err_code & IMG_INIT_PNG, exit);

    // Create an application g_game_state.p_window with the following settings:
    g_game_state.p_window = SDL_CreateWindow( "Hello World",           // g_game_state.p_window title
                                              SDL_WINDOWPOS_UNDEFINED, // initial x position
                                              SDL_WINDOWPOS_UNDEFINED, // initial y position
                                              g_game_state.window_w,   // width, in pixels
                                              g_game_state.window_h,   // height, in pixels
                                              0 );                     // flags
    require( g_game_state.p_window != NULL, exit );

    g_game_state.p_renderer = SDL_CreateRenderer(g_game_state.p_window, -1, SDL_RENDERER_ACCELERATED);
    require( g_game_state.p_renderer != NULL, exit );

    // Set the draw color to black
    err_code = SDL_SetRenderDrawColor(g_game_state.p_renderer, 0, 0, 0, 255);
    require_noerr(err_code, exit);

    // Clear the entire screen to our selected color
    err_code = SDL_RenderClear(g_game_state.p_renderer);
    require_noerr(err_code, exit);

    // Load assets
    err_code = CharAssets_Load(g_game_state.p_renderer, &g_game_state.char_assets);
    require_noerr(err_code, exit);


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
    SDL_DestroyRenderer(g_game_state.p_renderer);
    SDL_DestroyWindow(g_game_state.p_window);

    free_textures( g_game_state.char_assets.textures,
                   ARRAY_LEN(g_game_state.char_assets.textures) );

    printf( "Error: %s\n", SDL_GetError() );
    SDL_Quit();

    return 0;
}
