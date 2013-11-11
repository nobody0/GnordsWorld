#include "main.h"
#include <time.h>

#define FRAME_VALUES 10

int32_t SCREEN_WIDTH = 1024;
int32_t SCREEN_HEIGHT = 768;

int32_t GRID_SIZE = 32;

int32_t VISIBLE_GRIDS_X = SCREEN_WIDTH/GRID_SIZE + 4;
int32_t VISIBLE_GRIDS_Y = SCREEN_WIDTH/GRID_SIZE + 4;

int32_t UPDATE_GRID_OUT_VIEW_SIZE = 16;

const string BASE_IMAGE_PATH = "gfx/images/";
const string BASE_FONT_PATH = "gfx/fonts/";

SDL_Surface * screen = NULL;

SDL_Surface * lightScreen = NULL;

Uint32* lightMap = NULL;

int pixelCount = 0;

SDL_Event event;

Uint8 *keystates;

bool mouseDown = false;
uint16_t mouseX;
uint16_t mouseY;

bool showFrames = false;

float deltaTime = 0;
float totalTime = 0;
bool doShadeScreen = true;

World world;

int32_t MY_RAND_SEED = time(NULL);
int32_t myRand(int32_t x)
{
    x = (x*362436069+521288629) ^ MY_RAND_SEED;
    int32_t w = 88675123;
    int32_t t = x ^ (x << 11);
    return (w ^ (w >> 19) ^ (t ^ (t >> 8)));
}

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

	TTF_Init();

    if( (screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF )) == NULL )
    {
        return false;
    }

	const SDL_PixelFormat& fmt = *(screen->format);
    if( (lightScreen = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, fmt.BitsPerPixel, fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask)) == NULL )
    {
        return false;
    }

	pixelCount = screen->w*screen->h;

	lightMap = new Uint32[pixelCount];

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if( (initted & flags) != flags)
	{
		return false;
	}

    SDL_WM_SetCaption( "Hello 2D World", NULL );

    return true;
}

unordered_map<string, SDL_Surface*> loadedImages;

SDL_Surface *load_image( const string &filename )
{
	unordered_map<string, SDL_Surface*>::const_iterator it = loadedImages.find (filename);

	if ( it == loadedImages.end() )
	{
		//The image that's loaded
		SDL_Surface* loadedImage = NULL;

		//The optimized surface that will be used
		SDL_Surface* optimizedImage = NULL;

		//Load the image
		loadedImage = IMG_Load( ("../"+BASE_IMAGE_PATH+filename).c_str() );
		if (loadedImage == NULL) loadedImage = IMG_Load( (BASE_IMAGE_PATH+filename).c_str() );

		//If the image loaded
		if( loadedImage != NULL )
		{
			//Create an optimized surface
			optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

			//Free the old surface
			SDL_FreeSurface( loadedImage );
		}
		else
		{
			throw new exception("file couldnt be loaded");
		}

		loadedImages.insert(make_pair(filename, optimizedImage));

		//Return the optimized surface
		return optimizedImage;
	}
	else
	{
		return it->second;
	}
}

unordered_map<string, TTF_Font*> loadedFonts;

TTF_Font* load_font( const string &filename, const int size )
{
	unordered_map<string, TTF_Font*>::const_iterator it = loadedFonts.find (filename);

	if (it != loadedFonts.end())
	{
		return it->second;
	}

	TTF_Font* font = TTF_OpenFont(("../" + BASE_FONT_PATH + filename).c_str(), size);
	if (font == NULL) font = TTF_OpenFont((BASE_FONT_PATH + filename).c_str(), size);
	
	if (font == NULL)
	{
		throw new exception("file couldnt be loaded");
	}

	loadedFonts.insert(make_pair(filename + "##" + to_string(size), font));

	return font;
}

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

void shade_screen()
{
	SDL_LockSurface(screen);

	Uint8* colors = (Uint8*)screen->pixels;
	Uint8* shades = (Uint8*)lightMap;

	for( int i = (pixelCount*4)-1; i >= 0; i--)
	{
		(*colors) = ((*colors) * (*shades)) >> 8;
		colors++;
		shades++;
	}

	SDL_UnlockSurface(screen);
}

void apply_surface( const int32_t &x, const int32_t &y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void apply_font( const int32_t &x, const int32_t &y, SDL_Surface* destination, TTF_Font* font, const string text, const SDL_Color color )
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	apply_surface(x, y, textSurface, destination);
	SDL_FreeSurface(textSurface);
}


SDL_Surface* flip_surface( SDL_Surface *surface, int flags )
{
    //Pointer to the soon to be flipped surface
    SDL_Surface *flipped = NULL;

    //If the image is color keyed
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
    {
        //Go through rows
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
            //Get pixel
            Uint32 pixel = get_pixel32( surface, x, y );

            //Copy pixel
            if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
            {
                put_pixel32( flipped, rx, ry, pixel );
            }
            else if( flags & FLIP_HORIZONTAL )
            {
                put_pixel32( flipped, rx, y, pixel );
            }
            else if( flags & FLIP_VERTICAL )
            {
                put_pixel32( flipped, x, ry, pixel );
            }
        }
    }

    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }

    //Return flipped surface
    return flipped;
}


Uint32 frameTimes [FRAME_VALUES];
Uint32 frameTimeLast;
Uint32 frameCount;
float framesPerSecound;

void FpsInit()
{
	memset (frameTimes, 0, sizeof(frameTimes));
	frameCount = 0;
	framesPerSecound = 0;
	frameTimeLast = SDL_GetTicks();
}

void FpsLogic()
{
	Uint32 frameTimeIndex;
	Uint32 getTicks;
	Uint32 count;
	//Uint32 i;

	frameTimeIndex = frameCount % FRAME_VALUES;
	getTicks = SDL_GetTicks();
	frameTimes[frameTimeIndex] = getTicks - frameTimeLast;
	frameTimeLast = getTicks;
	frameCount++;

	if (frameCount < FRAME_VALUES)
	{
		count = frameCount;
	}
	else
	{
		count = FRAME_VALUES;
	}

	framesPerSecound = 0;
	for (Uint32 i = 0; i < count; i++)
	{
		framesPerSecound += frameTimes[i];
	}

	framesPerSecound /= count;
	framesPerSecound = 1000.f / framesPerSecound;
}

int main( int argc, char* args[] )
{
	float sinceStartTick;
    bool quit = false;

    if( !init() )
    {
        return 1;
    }

	world.init();

	

    while( !quit )
    {
		sinceStartTick = (float) SDL_GetTicks();
		deltaTime = sinceStartTick/1000 - totalTime;
		totalTime = sinceStartTick/1000;

		keystates = SDL_GetKeyState( NULL );

        while( SDL_PollEvent( &event ) )
        {
			switch(event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == SDLK_ESCAPE )
				{
					quit = true;
				}
				else if (event.key.keysym.sym == SDLK_f)
				{
					showFrames = !showFrames;
				}
				else if ( event.key.keysym.sym == SDLK_c )
				{
					doShadeScreen = !doShadeScreen;
				}
				break;
			case SDL_MOUSEMOTION :
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					mouseDown = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					mouseDown = false;
				}
				break;
			}
        }

		if (mouseDown)
		{
			world.onClick();
		}

		world.update();

		//lighting demo
		if (doShadeScreen)
		{
			shade_screen();
		}

		//fps
		if (showFrames == true)
		{
			SDL_Color color = {0,255,255};
			apply_font(100, 100, screen, load_font("arial.ttf", 55), to_string(framesPerSecound) , color);
		}

		//perlin demo
		/*
		SDL_Surface* perlin;

		perlin = PerlinNoise::Render_Clouds(0, 0, 100, 100, 75, 0.25);
		apply_surface(0, 0, perlin, screen);
		SDL_FreeSurface(perlin);

		perlin = PerlinNoise::Render_Clouds(100, 0, 100, 100, 75, 0.25);
		apply_surface(100, 0, perlin, screen);
		SDL_FreeSurface(perlin);

		perlin = PerlinNoise::Render_Clouds(200, 0, 100, 100, 75, 0.25);
		apply_surface(200, 0, perlin, screen);
		SDL_FreeSurface(perlin);
		*/

		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}

		FpsLogic();
		
    }
	
	TTF_Quit();
    SDL_Quit();

    return 0;
}
