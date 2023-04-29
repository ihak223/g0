#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "linkedlists.h"
#include "game.h"





typedef SDL_Surface* asset;





int init_asset_loader()
{
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    if ((IMG_Init(flags)&flags) != flags)
    {
        printf("IIE! IMG: %s\n", IMG_GetError());
        return -1;
    }
    return 1;
}

SDL_Surface* map_asset_stb(const char* filename) {
    printf("*Loading asset %s\n", filename);
    // Load PNG file into a raw pixel buffer using stb_image
    int width, height, channels;
    unsigned char* pixels = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    if (!pixels) {
        printf("Error loading PNG file %s: %s\n", filename, stbi_failure_reason());
        return NULL;
    }

    // Create an SDL_Surface from the pixel buffer
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        printf("Error creating SDL_Surface from PNG file %s: %s\n", filename, SDL_GetError());
        stbi_image_free(pixels);
        return NULL;
    }

    return surface;
}

asset map_asset(SDL_Surface* f, const char* path)
{
    printf("loading asset %s...\n", path);
    asset img = IMG_Load(path);
    if (!img)
    {
        printf("ILE! IMG: %s\n", IMG_GetError());
    }
    asset texture2 = SDL_CreateRGBSurfaceWithFormat(0, 16, 16, f->format->BitsPerPixel, f->format->format);
    texture2 = SDL_ConvertSurface(img, f->format, 0);
    printf("-a-%d %d\n", texture2, img);
    SDL_FreeSurface(img);
    return texture2;
}

Node load_asset_node(char* path, int id)
{
    

    printf("*created surface\n");
    SDL_Surface* texture = map_asset_stb(path);
    printf("*mapped asset\n");
    return alloc_node(texture, id);
}

asset get_asset(Node a)
{
    return (asset)a->data;
}

