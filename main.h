#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "World.h"

using namespace std;

extern int32_t SCREEN_WIDTH;
extern int32_t SCREEN_HEIGHT;

extern int32_t GRID_SIZE;

extern int32_t VISIBLE_GRIDS_X;
extern int32_t VISIBLE_GRIDS_Y;

extern int32_t UPDATE_GRID_OUT_VIEW_SIZE;

const int32_t SCREEN_BPP = 32;

extern const string BASE_IMAGE_PATH;

extern SDL_Surface *screen;

extern SDL_Event event;

extern Uint8 *keystates;

extern float deltaTime;
extern float totalTime;

extern SDL_Surface *SURFACE_EISEN_1;
extern SDL_Surface *SURFACE_EISEN_2;
extern SDL_Surface *SURFACE_EISEN_3;
extern SDL_Surface *SURFACE_EISEN_4;
extern SDL_Surface *SURFACE_EISEN_5;
extern SDL_Surface *SURFACE_EISEN_6;
extern SDL_Surface *SURFACE_ERDE_1;
extern SDL_Surface *SURFACE_ERDE_2;
extern SDL_Surface *SURFACE_ERDE_3;
extern SDL_Surface *SURFACE_ERDE_4;
extern SDL_Surface *SURFACE_ERDE_5;
extern SDL_Surface *SURFACE_ERDE_6;
extern SDL_Surface *SURFACE_GRAS_1;
extern SDL_Surface *SURFACE_GRAS_2;
extern SDL_Surface *SURFACE_GRAS_3;
extern SDL_Surface *SURFACE_GRAS_4;
extern SDL_Surface *SURFACE_GRAS_5;
extern SDL_Surface *SURFACE_GRAS_6;
extern SDL_Surface *SURFACE_KOHLE_1;
extern SDL_Surface *SURFACE_KOHLE_2;
extern SDL_Surface *SURFACE_KOHLE_3;
extern SDL_Surface *SURFACE_KOHLE_4;
extern SDL_Surface *SURFACE_KOHLE_5;
extern SDL_Surface *SURFACE_KOHLE_6;
extern SDL_Surface *SURFACE_KUPFER_1;
extern SDL_Surface *SURFACE_KUPFER_2;
extern SDL_Surface *SURFACE_KUPFER_3;
extern SDL_Surface *SURFACE_KUPFER_4;
extern SDL_Surface *SURFACE_KUPFER_5;
extern SDL_Surface *SURFACE_KUPFER_6;
extern SDL_Surface *SURFACE_MOOSGRAS_5;
extern SDL_Surface *SURFACE_SILBER_1;
extern SDL_Surface *SURFACE_SILBER_2;
extern SDL_Surface *SURFACE_SILBER_3;
extern SDL_Surface *SURFACE_SILBER_4;
extern SDL_Surface *SURFACE_SILBER_5;
extern SDL_Surface *SURFACE_SILBER_6;
extern SDL_Surface *SURFACE_STEIN_1;
extern SDL_Surface *SURFACE_STEIN_2;
extern SDL_Surface *SURFACE_STEIN_3;
extern SDL_Surface *SURFACE_STEIN_4;
extern SDL_Surface *SURFACE_STEIN_5;
extern SDL_Surface *SURFACE_STEIN_6;
extern SDL_Surface *SURFACE_PLAYER;

extern World world;

extern int32_t MY_RAND_SEED;
extern int32_t myRand(int32_t x);

extern bool init();

extern SDL_Surface *load_image( std::string filename );

extern void apply_surface( int32_t x, int32_t y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

extern bool load_files();

extern void unload_files();