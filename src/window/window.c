#include "window.h"

#include <SDL2/SDL.h>

struct Window
{
        /* SDL structs */
        SDL_Window * win;
        SDL_Renderer * rend;
        SDL_Event event;

        /* attributes about window */
        uint16_t width;
        uint16_t height;

        /* flags */
        uint8_t shouldClose;
};

static int _init_SDL( void )
{
        return SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
}

struct Window* window_init( void )
{
        struct Window* win = malloc( sizeof(struct Window) );
        // if window and SDL inits successfully
        if ( win != NULL && _init_SDL() == 0 )
        {
                SDL_CreateWindowAndRenderer( WINDOW_W, WINDOW_H, 0, 
                                             &win->win, &win->rend );

                win->width = WINDOW_W;
                win->height = WINDOW_H;

                win->shouldClose = 0;
        }
 return win;
}

uint8_t window_free( struct Window* win )
{
        // destroy sdl stuff and q
        SDL_DestroyRenderer( win->rend );
        SDL_DestroyWindow( win->win );

        if ( win != NULL )
                free( win );

        return ( win != NULL );
}

uint8_t window_shouldClose( struct Window* win )
{
        return win->shouldClose;
}

void window_refresh( struct Window* win )
{
        // poll events
        while ( SDL_PollEvent( &win->event ) != 0 ) 
        {
                switch ( win->event.type )
                {
                        case SDL_QUIT:
                                win->shouldClose = 1;
                                break;
                        default:
                                break;
                }
        }
        
}
