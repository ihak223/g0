#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlists.h"
#include "game.h"
#include "lighting.h"
#include "initassets.h"
#include "cmath.h"

// starts SDL
int init_graphics(Game game, const int w, const int h)
{

    printf("Starting video init...");
    game->WIDTH = w;
    game->HEIGHT = h;
    // detects init errors
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("VIE! SDL : %s\n", SDL_GetError());
        return -1; // :(
    }

    printf("*Started video\n");

    game->window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    // makes sure window was created
    if (!game->window)
    {
        printf("WCE! SDL : %s\n", SDL_GetError());
        return -2; // -_-
    }

    printf("*Loaded window\n");

    game->surface = SDL_GetWindowSurface(game->window);

    printf("*Created surface\n");

    game->lighting_pixels = SDL_CreateRGBSurfaceWithFormat(0, game->surface->w, game->surface->h, game->surface->format->BitsPerPixel, game->surface->format->format);

    printf("*Created lighting pixels %d, %d, %d\n", game->lighting_pixels->h, game->lighting_pixels->w, game->lighting_pixels->format->format);

    int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
    if ((IMG_Init(flags)&flags) != flags)
    {
        printf("IIE! IMG: %s\n", IMG_GetError());
        return -3; // *_*
    }

    printf("*Initialized asset loader\n");

    // Load base asset
    game->dynamic_assets = load_asset_node("/home/halie/Repos/g0/src/assets/redtiles.png", 0);
    game->dynamic_assets->index = 0;

    game->dynamic_assets = append_node(game->dynamic_assets, load_asset_node("/home/halie/Repos/g0/src/assets/bigtile.png", 1));
    printf("a\n");
    
    printf("-a %d\n", game->dynamic_assets->index);
    game->dynamic_assets = append_node(game->dynamic_assets, load_asset_node("/home/halie/Repos/g0/src/assets/cobbled.png", 2));
    printf("-a %d\n", game->dynamic_assets->index);
    game->dynamic_assets = append_node(game->dynamic_assets, load_asset_node("/home/halie/Repos/g0/src/assets/floorboards.png", 3));
    printf("-a %d\n", game->dynamic_assets->index);




    return 0; // :)
}


// Exits SDL
int quit(Game game)
{
    SDL_DestroyWindow(game->window);

    free(game->surface);

    SDL_Quit();

    free(game);

    return 0;
}

void blit(int x, int y, SDL_Surface* source, SDL_Surface* dest)
{


    SDL_Rect destrect;
    destrect.x = x;
    destrect.y = y;
    destrect.h = source->h;
    destrect.w = source->w;


    SDL_BlitSurface(source, 0, dest, &destrect);
}
int a = 0;
int pos[] = {255, 255};



// Loop SDL
int loop(Game game, Uint32 quit_condition)
{
    SDL_Event e; // event to loop through
    int mx, my;  // mouse pos
    double sx, sy;
    // loops through events until pointer is 0
    while (SDL_PollEvent(&e))
    {
        if (e.type == quit_condition)
        {
            return 0;
        }
    }

    



   

    SDL_FillRect(game->surface, NULL, SDL_MapRGBA(game->surface->format, 0, 0, 0, 255));

    SDL_GetMouseState(&mx, &my);

    slope(&sx, &sy, 255, 255, mx, my);
    sx = (double)(mx-255);
    sy = (double)(my-255);
    printf("mp : %d, %d slope : %f, %f angle : %d                  \r", mx, my, sx, sy, ((int)get_angle(sy, sx))%360);


    cast_flashlight(game, 255, 255, (int)get_angle(sy, sx)%360);

    a++;

    SDL_UpdateWindowSurface(game->window);

    return 1;
}

int main()
{
    Game game = malloc(sizeof(struct Game));
    init_graphics(game, 512, 512);

    printf("finished init\n");

    
    int index;
    printf("enter int [0...3] ? ");
    scanf("%d", &index);

    printf("\nretriving asset : %d\n", index);
    
    asset texture = get_node(game->dynamic_assets, index)->data;
    
    
    
    for (int x = 0; x < 512; x = x + 16)
    {
        for (int y = 0; y < 512; y = y + 16)
        {
            blit(x, y, texture, game->lighting_pixels);
        }
    }
    printf("finished mapping\n");

    int lr = 1;

    while (lr)
    {
        lr = loop(game, SDL_QUIT);
        
    }

    quit(game);

    return 0;
}

