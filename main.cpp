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

float deltaTime = 0;
float totalTime = 0;

World world;

int32_t MY_RAND_SEED = 123456;
int32_t myRand(int32_t x)
{
	//TODO this does not look very much random!
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

SDL_Surface * load_image( std::string filename )
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
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
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

SDL_Surface *SURFACE_EISEN_1 = NULL;
SDL_Surface *SURFACE_EISEN_2 = NULL;
SDL_Surface *SURFACE_EISEN_3 = NULL;
SDL_Surface *SURFACE_EISEN_4 = NULL;
SDL_Surface *SURFACE_EISEN_5 = NULL;
SDL_Surface *SURFACE_EISEN_6 = NULL;
SDL_Surface *SURFACE_ERDE_1 = NULL;
SDL_Surface *SURFACE_ERDE_2 = NULL;
SDL_Surface *SURFACE_ERDE_3 = NULL;
SDL_Surface *SURFACE_ERDE_4 = NULL;
SDL_Surface *SURFACE_ERDE_5 = NULL;
SDL_Surface *SURFACE_ERDE_6 = NULL;
SDL_Surface *SURFACE_GRAS_1 = NULL;
SDL_Surface *SURFACE_GRAS_2 = NULL;
SDL_Surface *SURFACE_GRAS_3 = NULL;
SDL_Surface *SURFACE_GRAS_4 = NULL;
SDL_Surface *SURFACE_GRAS_5 = NULL;
SDL_Surface *SURFACE_GRAS_6 = NULL;
SDL_Surface *SURFACE_KOHLE_1 = NULL;
SDL_Surface *SURFACE_KOHLE_2 = NULL;
SDL_Surface *SURFACE_KOHLE_3 = NULL;
SDL_Surface *SURFACE_KOHLE_4 = NULL;
SDL_Surface *SURFACE_KOHLE_5 = NULL;
SDL_Surface *SURFACE_KOHLE_6 = NULL;
SDL_Surface *SURFACE_KUPFER_1 = NULL;
SDL_Surface *SURFACE_KUPFER_2 = NULL;
SDL_Surface *SURFACE_KUPFER_3 = NULL;
SDL_Surface *SURFACE_KUPFER_4 = NULL;
SDL_Surface *SURFACE_KUPFER_5 = NULL;
SDL_Surface *SURFACE_KUPFER_6 = NULL;
SDL_Surface *SURFACE_MOOSGRAS_5 = NULL;
SDL_Surface *SURFACE_SILBER_1 = NULL;
SDL_Surface *SURFACE_SILBER_2 = NULL;
SDL_Surface *SURFACE_SILBER_3 = NULL;
SDL_Surface *SURFACE_SILBER_4 = NULL;
SDL_Surface *SURFACE_SILBER_5 = NULL;
SDL_Surface *SURFACE_SILBER_6 = NULL;
SDL_Surface *SURFACE_STEIN_1 = NULL;
SDL_Surface *SURFACE_STEIN_2 = NULL;
SDL_Surface *SURFACE_STEIN_3 = NULL;
SDL_Surface *SURFACE_STEIN_4 = NULL;
SDL_Surface *SURFACE_STEIN_5 = NULL;
SDL_Surface *SURFACE_STEIN_6 = NULL;

SDL_Surface *SURFACE_PLAYER = NULL;

bool load_files()
{
    if( (SURFACE_ERDE_1 = load_image( "erz_erde1.jpg" )) == NULL )  return false;
    if( (SURFACE_ERDE_2 = load_image( "erz_erde2.jpg" )) == NULL )  return false;
    if( (SURFACE_ERDE_3 = load_image( "erz_erde3.jpg" )) == NULL ) return false;
    if( (SURFACE_ERDE_4 = load_image( "erz_erde4.jpg" )) == NULL ) return false;
    if( (SURFACE_ERDE_5 = load_image( "erz_erde5.jpg" )) == NULL ) return false;
    if( (SURFACE_ERDE_6 = load_image( "erz_erde6.jpg" )) == NULL ) return false;
	
    if( (SURFACE_GRAS_1 = load_image( "erz_gras1.jpg" )) == NULL )  return false;
    if( (SURFACE_GRAS_2 = load_image( "erz_gras2.jpg" )) == NULL )  return false;
    if( (SURFACE_GRAS_3 = load_image( "erz_gras3.jpg" )) == NULL )  return false;
    if( (SURFACE_GRAS_4 = load_image( "erz_gras4.jpg" )) == NULL )  return false;
    if( (SURFACE_GRAS_5 = load_image( "erz_gras5.jpg" )) == NULL )  return false;
    if( (SURFACE_GRAS_6 = load_image( "erz_gras6.jpg" )) == NULL )  return false;

    if( (SURFACE_PLAYER = load_image( "player.bmp" )) == NULL )  return false;

    return true;
}

void unload_files()
{
    SDL_FreeSurface( SURFACE_ERDE_1 );
    SDL_FreeSurface( SURFACE_ERDE_2 );
    SDL_FreeSurface( SURFACE_ERDE_3 );
    SDL_FreeSurface( SURFACE_ERDE_4 );
    SDL_FreeSurface( SURFACE_ERDE_5 );
    SDL_FreeSurface( SURFACE_ERDE_6 );
	
    SDL_FreeSurface( SURFACE_GRAS_1 );
    SDL_FreeSurface( SURFACE_GRAS_2 );
    SDL_FreeSurface( SURFACE_GRAS_3 );
    SDL_FreeSurface( SURFACE_GRAS_4 );
    SDL_FreeSurface( SURFACE_GRAS_5 );
    SDL_FreeSurface( SURFACE_GRAS_6 );
}

int main( int argc, char* args[] )
{
	float sinceStartTick;
    bool quit = false;

    if( !init() )
    {
        return 1;
    }

    if( !load_files() )
    {
        return 1;
    }

	world.init();

    while( !quit )
    {
		sinceStartTick = (float) SDL_GetTicks();
		deltaTime = sinceStartTick/1000 - totalTime;
		totalTime = sinceStartTick/1000;

        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }

		keystates = SDL_GetKeyState( NULL );

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
