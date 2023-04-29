#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include "cmath.h"
#include "linkedlists.h"
#include "game.h"




void draw_line(SDL_Surface* surface, double x1, double y1, double x2, double y2, Uint32 color)
{
    double x = x1;
    double y = y1;

    double dx = x2-x1;
    double dy = y2-y1;
    double ds = 2 * dy - dx;

    double d = 0;

    double length = sqrt((dx * dx) + (dy * dy));

    double s = dx / length;
    double c = dy / length;

    while (x <= x2)
    {
        
        x = x + 1;
        if (d <= 0)
        {
            d = d + s;
            ds = ds + 2 * dy;
        }
        else
        {
            d = d + s - c;
            ds = ds + 2 * (dy - dx);
            y = y + 1;
        }
    }


}

void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
      Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
      *(Uint32 *)target_pixel = pixel;
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
                break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void amp_pixel(Game game, int x, int y, double d)
{
    Uint32 pixel = get_pixel(game->lighting_pixels, x, y);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    SDL_GetRGBA(pixel, game->surface->format, &r, &g, &b, &a);
    r = (int)r / (d+1);
    g = (int)g / (d+1);
    b = (int)b / (d+1); 

    set_pixel(game->surface, x, y, SDL_MapRGBA(game->surface->format, r, g, b, a));
    
    
}

void cast_ray(Game game, double angle, double x, double y, int l)
{
    int c = 1;
    double sx;
    double sy;

    

    slope_from_angle(&sx, &sy, angle);

    while (c < l)
    {
        
        amp_pixel(game, (int)x, (int)y, ((double)c)/50);
        amp_pixel(game, (int)x, (int)y+1, ((double)c)/25);
        amp_pixel(game, (int)x, (int)y-1, ((double)c)/25);
        
        x += sx;
        y += sy;
        c++;
        
    }
}

void cast_flashlight(Game game, int x, int y, double angle)
{

    

    double current_angle = angle - 60;

    while (current_angle < (angle + 60))
    {
        cast_ray(game, current_angle, x, y, 200);
        current_angle ++;
    }

}