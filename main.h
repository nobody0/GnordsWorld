#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "World.h"
#include <iostream>

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

extern uint16_t mouseX;
extern uint16_t mouseY;

extern float deltaTime;
extern float totalTime;

extern World world;

extern int32_t MY_RAND_SEED;
extern int32_t myRand(int32_t x);

extern SDL_Surface *load_image( const string &filename );

extern void apply_surface( int32_t x, int32_t y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );