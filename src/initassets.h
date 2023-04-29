typedef SDL_Surface* asset;

int init_asset_loader();
asset map_asset(SDL_Surface* f, const char* path);

Node load_asset_node(const char* path, int id);

asset get_asset(Node a);
asset map_asset_stb(const char* filename);