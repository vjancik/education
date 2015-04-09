#include "functions.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
SDL_Surface* screen = NULL;
bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL ) return false;
	if( TTF_Init() == -1 ) return false;
	SDL_WM_SetCaption( "Ping Pong", NULL );
    return true;
}

SDL_Surface *load_image( std::string filename ) 
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load( filename.c_str() );
	if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
		if( optimizedImage != NULL )
        {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
	return optimizedImage;
}
//SURFACES #####################
SDL_Surface* home = NULL;
SDL_Surface* newbutton = NULL;
SDL_Surface* endbutton = NULL;
//SURFACES #####################
bool load_files()
{
    home = load_image( "home.png" );
	newbutton = load_image( "new.png" );
	endbutton = load_image( "end.png" );
	if( home == NULL ) return false;
	if( newbutton == NULL ) return false;
	if( endbutton == NULL ) return false;
    return true;    
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool initrender()
{
	apply_surface (0,0, home, screen );
	apply_surface ((SCREEN_WIDTH - newbutton->w ) / 2,350 - newbutton->h , newbutton, screen );
	apply_surface ((SCREEN_WIDTH - endbutton->w ) / 2,550 - endbutton->h , endbutton, screen );
	SDL_Flip( screen );
	return true;
}
SDL_Event event;
bool quit = false;
void events()
{
	while( SDL_PollEvent( &event ) )
    {	
		if( event.type == SDL_QUIT ) quit = true;
	}
}
void cycle() 
{
	while( quit == false )
    {
		events();
	}
}
void clean_up()
{
    SDL_FreeSurface( home );
	SDL_FreeSurface( newbutton );
	SDL_FreeSurface( endbutton );
	TTF_Quit();
    SDL_Quit();    
}