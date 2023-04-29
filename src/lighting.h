void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
void cast_ray(Game game, double angle, double x, double y, int l);
void cast_flashlight(Game game, int x, int y, double angle);
void amp_pixel(Game game, int x, int y);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);