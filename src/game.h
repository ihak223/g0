

struct Game
{
    SDL_Window* window;
    SDL_Surface* surface;

    SDL_Surface* lighting_pixels;
    int WIDTH;
    int HEIGHT;

    Node dynamic_assets;

};

typedef struct Game* Game;