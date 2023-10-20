#include "draw_routines.h"
#include "sdl_wrapper.h"

#include "../error-handler/error-handler.h"
#include "../constants.h"
#include "../tilemap.h"

#include <SDL2/SDL.h>

static void _draw_tile( struct Window* win, int tile,
			unsigned int x, unsigned int y )
{
	if ( tile != 0 )
	{
		struct ImgTex* tileset = win_getAsset( win, 0 );
		SDL_Texture* tile_tex = imgtex_getTex( tileset );

		SDL_Rect tile_pos = imgtex_getTilePos( tileset, tile );
		SDL_Rect screen_pos = { x* TILE_SZ*SCALE, y * TILE_SZ*SCALE,
			                TILE_SZ*SCALE, TILE_SZ*SCALE };
		
		SDL_RenderCopy( win_getRenderer( win ), tile_tex,
				&tile_pos, &screen_pos );
	}
}

void _draw_tilemap( struct Window* win, struct Tilemap* tm )
{
	for ( unsigned int x = 0; x < (unsigned int)tm_getW( tm ); x++ )
	{
                for ( unsigned int y = 0; y < (unsigned int)tm_getH( tm ); y++ )
		{
                        _draw_tile( win, tm_get_tile( tm, x, y ), x, y );
		}
	}
}
