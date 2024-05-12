#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "macros.h"

#ifdef WASM
#include <emscripten.h>
#endif

static SDL_Window*   window;
static SDL_Renderer* renderer;
static SDL_Texture*  texture;

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
    err_code = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    check_noerr(err_code);

    // Clear the entire screen to our selected color
    err_code = SDL_RenderClear(renderer);
    check_noerr(err_code);

    int texWidth, texHeight;

    err_code = SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);  // Get the width and height of the texture
    check_noerr(err_code);

    texHeight *= 2;
    texWidth  *= 2;

    SDL_Rect dstRect;
    dstRect.x = (640 - texWidth) / 2;  // Center the image horizontally
    dstRect.y = (480 - texHeight) / 2;  // Center the image vertically
    dstRect.w = texWidth;  // Use the original image width
    dstRect.h = texHeight;  // Use the original image height

    err_code = SDL_RenderCopy(renderer, texture, NULL, &dstRect);  // Draw the image
    check_noerr(err_code);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, white contents of the window.
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_image with PNG support
    IMG_Init(IMG_INIT_PNG);

    // Create an application window with the following settings:
    window = SDL_CreateWindow( "Hello World",           // window title
                               SDL_WINDOWPOS_UNDEFINED, // initial x position
                               SDL_WINDOWPOS_UNDEFINED, // initial y position
                               640,                     // width, in pixels
                               480,                     // height, in pixels
                               0 );                     // flags
    require( window != NULL, err_handler );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    require( renderer != NULL, err_handler );

    texture = IMG_LoadTexture(renderer, "assets/ACharDown.png");
    require( texture != NULL, err_handler );

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif

    return 0;

err_handler:
    printf( "Error: %s\n", SDL_GetError() );
    SDL_Quit();
    return 1;
}
