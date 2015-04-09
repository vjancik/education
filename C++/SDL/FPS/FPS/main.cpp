#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <cstring>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

SDL_Surface *image = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
TTF_Font *font = NULL;

SDL_Event event;

SDL_Color textColor = { 0, 0, 0 };

class Timer
{
    private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
    public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
};
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
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    return optimizedImage;
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL ) return false;
	if( TTF_Init() == -1 ) return false;
    SDL_WM_SetCaption( "Frame Rate Test", NULL );
    return true;
}
bool load_files()
{
    image = load_image( "testing.png" );
	font = TTF_OpenFont( "lazy.ttf", 50 );
    if( image == NULL ) return false;
	if( font == NULL ) return false;
    return true;
}
void clean_up()
{
    SDL_FreeSurface( image );
	TTF_CloseFont( font );
    SDL_Quit();
}
Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}
void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}
void Timer::stop()
{
    started = false;
    paused = false;
}
void Timer::pause()
{
    if( ( started == true ) && ( paused == false ) )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}
void Timer::unpause()
{
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}
int Timer::get_ticks()
{
    if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}
bool Timer::is_started()
{
    return started;
}
bool Timer::is_paused()
{
    return paused;
}
int main( int argc, char* args[] )
{
    bool quit = false;
    int frame = 0;
	bool cap = true;
    Timer fps;
    Timer update;
	Timer time;
    if( init() == false )
    {
        return 1;
    }
    if( load_files() == false )
    {
        return 1;
    }
    update.start();
	time.start();
    while( quit == false )
    {
		fps.start();
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        apply_surface( 0, 0, image, screen );
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        frame++;
		if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
		if(update.get_ticks() > 1000)
        {
            std::stringstream caption;
            caption << "Average Frames Per Second: " << frame / ( time.get_ticks() / 1000 );
			message = TTF_RenderText_Solid( font, "Hello", textColor );
			apply_surface( 100 ,100, message, screen );
            SDL_WM_SetCaption( caption.str().c_str(), NULL );
			update.start();
        }
    }
    clean_up();
    return 0;
}