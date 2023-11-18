#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../../constants.h"
#include "../structures/queue.h"
#include "window.h"
#include "draw_routines.h"
#include "imgtex.h"

struct Window
{
        SDL_Window* window;
	SDL_Renderer* renderer;

	struct ImgTex** assets;
	
	struct Queue* drawqueue;
};

/* _initSDL()
 * ==========
 * Initializes SDL with the given flags.
 */
static void _initSDL()
{
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
                err_report( FATAL, "SDL failed to initialize." );
        }
}

/* _loadAssets()
 * =============
 * Loads all image assets found into the Window struct (as a dynamic array).
 */
static void _loadAssets( struct Window* win )
{
        //temp; load only example tileset
	win->assets = malloc( sizeof(struct ImgTex*) * 2 );
	win->assets[0] = imgtex_init( win->renderer,
				      "assets/tilesets/test.json" );
        win->assets[1] = imgtex_init( win->renderer, 
                                      "assets/tilesets/text.json" );
}

struct Window* win_init()
{
        /* Initialize SDL */
        _initSDL();

        /* Allocate and populate Window struct */
        struct Window* win = malloc( sizeof(struct Window) );
        if ( win == NULL )
                err_report( FATAL, "Could not malloc() Window struct!" );
        
        SDL_CreateWindowAndRenderer( WIN_WIDTH, WIN_HEIGHT, 0,
				     &win->window, &win->renderer );

	/* Load assets */
	_loadAssets( win );

        /* Create Drawqueue */
        win->drawqueue = dq_init();
	
        return win;
}

void win_free( struct Window* win )
{
        SDL_DestroyRenderer( win->renderer );
	SDL_DestroyWindow( win->window );
        free( win );
        SDL_Quit();
}

struct DQItem
{
        void* item;
	enum ItemType it;
	ui_vec2_t pos;
};

void win_addToQueue( struct Window* win, enum ItemType it, void* item,
		     ui_vec2_t pos )
{
        struct DQItem* dq_item = malloc( sizeof(struct DQItem) );
	dq_item->item = item;
	dq_item->it = it;
	dq_item->pos = pos;

	dq_add( win->drawqueue, dq_item );
}

void win_drawFrame( struct Window* win )
{
	SDL_RenderClear( win->renderer );
	SDL_SetRenderDrawColor( win->renderer, 0, 0, 0, 255);
        for ( unsigned int i = 0; i < dq_getSz( win->drawqueue ); i++ )
	{
		struct DQItem* dq_item = dq_get( win->drawqueue );

		switch (dq_item->it)
		{
		case ROOM_TYPE:
			_draw_room( win, (struct Room*)dq_item->item );
			break;
                case TEXT_TYPE:
                        _draw_text( win, (struct Text*)dq_item->item );
                        break;
                default:
			break;
		}

		/* Free DQItem but not contents */
		free( dq_item );
	}

}

void win_flip( struct Window* win )
{
	SDL_RenderPresent( win->renderer );
}

void* win_getRenderer( struct Window* win )
{
	return (void*)win->renderer;
}

struct ImgTex* win_getAsset( struct Window* win, uint8_t index )
{
        return win->assets[index];
}

void win_drawCursor( struct Window* win, ui_vec2_t pos )
{
        SDL_Rect cursor = { pos.x*TILE_SZ*SCALE, pos.y*TILE_SZ*SCALE,
		            TILE_SZ*SCALE, TILE_SZ*SCALE };
	SDL_Renderer* win_renderer = SDL_GetRenderer( win->window );
	
	SDL_SetRenderDrawColor(win_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect( win_renderer, &cursor );
	SDL_SetRenderDrawColor( win->renderer, 0, 0, 0, 255);
}
