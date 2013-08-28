//The headers
#include "main.h"

int32_t SCREEN_WIDTH = 640;
int32_t SCREEN_HEIGHT = 480;

int32_t GRID_SIZE = 32;

int32_t VISIBLE_GRIDS_X = SCREEN_WIDTH/GRID_SIZE + 4;
int32_t VISIBLE_GRIDS_Y = SCREEN_WIDTH/GRID_SIZE + 4;

int32_t UPDATE_GRID_OUT_VIEW_SIZE = 64;

const string BASE_IMAGE_PATH = "gfx/images/";

SDL_Surface * screen = NULL;

SDL_Event event;

Uint8 *keystates;

uint16_t mouseX;
uint16_t mouseY;

float deltaTime = 0;
float totalTime = 0;

World world;

int32_t MY_RAND_SEED = 123456;
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

    if( (screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE )) == NULL )
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
		loadedImage = IMG_Load( (BASE_IMAGE_PATH+filename).c_str() );

		//If the image loaded
		if( loadedImage != NULL )
		{
			//Create an optimized surface
			optimizedImage = SDL_DisplayFormat( loadedImage );

			//Free the old surface
			SDL_FreeSurface( loadedImage );

			//If the surface was optimized
			if( optimizedImage != NULL )
			{
				//Color key surface
				//SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF ) );
			}
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

void unload_files()
{

}


void apply_surface( int32_t x, int32_t y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
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
				break;
			case SDL_MOUSEMOTION :
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					world.onClick();
				}
				break;
			}
        }

		world.update();

		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}
    }

    SDL_Quit();

	unload_files();

    return 0;
}
