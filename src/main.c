#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "macros.h"

#ifdef WASM
#include <emscripten.h>
#endif

static SDL_Window*   gp_window;
static SDL_Renderer* gp_renderer;
static SDL_Texture*  gp_texture;

#ifndef WASM
    #define FRAME_RATE          ( 60 )
    #define FRAME_TIME_TICKS    ( 1000 / FRAME_RATE )

    static uint32_t g_quit = 0;
#endif

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


    // Set the draw color to white
    err_code = SDL_SetRenderDrawColor(gp_renderer, 0, 0, 0, 255);
    check_noerr(err_code);

    // Clear the entire screen to our selected color
    err_code = SDL_RenderClear(gp_renderer);
    check_noerr(err_code);

    int texWidth, texHeight;

    err_code = SDL_QueryTexture(gp_texture, NULL, NULL, &texWidth, &texHeight);  // Get the width and height of the gp_texture
    check_noerr(err_code);

    texHeight *= 2;
    texWidth  *= 2;

    SDL_Rect dstRect;
    dstRect.x = (640 - texWidth) / 2;  // Center the image horizontally
    dstRect.y = (480 - texHeight) / 2;  // Center the image vertically
    dstRect.w = texWidth;  // Use the original image width
    dstRect.h = texHeight;  // Use the original image height

    err_code = SDL_RenderCopy(gp_renderer, gp_texture, NULL, &dstRect);  // Draw the image
    check_noerr(err_code);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, white contents of the gp_window.
    SDL_RenderPresent(gp_renderer);
}

int main(int argc, char* argv[])
{
    int err_code = 0;

    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_image with PNG support
    err_code = IMG_Init(IMG_INIT_PNG);
    require(err_code & IMG_INIT_PNG, exit);

    // Create an application gp_window with the following settings:
    gp_window = SDL_CreateWindow( "Hello World",           // gp_window title
                               SDL_WINDOWPOS_UNDEFINED, // initial x position
                               SDL_WINDOWPOS_UNDEFINED, // initial y position
                               640,                     // width, in pixels
                               480,                     // height, in pixels
                               0 );                     // flags
    require( gp_window != NULL, exit );

    gp_renderer = SDL_CreateRenderer(gp_window, -1, SDL_RENDERER_ACCELERATED);
    require( gp_renderer != NULL, exit );

    gp_texture = IMG_LoadTexture( gp_renderer, PATH_CONCAT3(ASSETS_PATH, "character", "down1.png") );
    require( gp_texture != NULL, exit );

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
    SDL_DestroyRenderer(gp_renderer);
    SDL_DestroyWindow(gp_window);
    SDL_DestroyTexture(gp_texture);

    printf( "Error: %s\n", SDL_GetError() );
    SDL_Quit();

    return 0;
}
