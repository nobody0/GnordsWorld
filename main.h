#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "PerlinNoise.h"
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
extern const string BASE_FONT_PATH;

extern void FpsLogic();

extern void FpsInit();

//Flip flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

extern SDL_Surface *screen;

extern SDL_Surface *lightScreen;

extern int lightPrecision;
extern int lightPrecisionDelta;

extern Uint32* lightMap;

#define dayTimeMax 1440
extern int dayTime;

extern unsigned int pixelCount;

extern SDL_Event event;

extern Uint8 *keystates;

extern bool mouseDown;
extern uint16_t mouseX;
extern uint16_t mouseY;

extern float deltaTime;
extern float totalTime;

extern bool doShadeScreen;

extern bool showInventory;

extern World world;

extern int32_t MY_RAND_SEED;
extern int32_t myRand(int32_t x);

extern SDL_Surface *load_image( const string &filename );

extern TTF_Font* load_font( const string &filename, const int size = 14 );

extern Uint32 get_pixel32( SDL_Surface *surface, int x, int y );

extern void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );

extern void shade_screen();

extern void apply_surface( const int32_t &x, const int32_t &y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

extern void apply_font( const int32_t &x, const int32_t &y, SDL_Surface* destination, TTF_Font* font, const string text, const SDL_Color color );

extern SDL_Surface* flip_surface( SDL_Surface *surface, int flags );