#define GRAPHICS_NS

#include "../../constants.h"
#include "../events/error-handler.h"
#include "draw_routines.h"

#include <SDL2/SDL.h>
#include <string.h>

#include <stdio.h>

static void _draw_tile( struct Window* win, struct Tile tile,
			unsigned int x, unsigned int y )
{
	if ( tile.type != 0 && tile.is_visible )
	{
		struct ImgTex* tileset = win_getAsset( win, 0 );
		SDL_Texture* tile_tex = imgtex_getTex( tileset );

		SDL_Rect tile_pos = imgtex_getTilePos( tileset, tile.type );
		SDL_Rect screen_pos = { x* TILE_SZ*SCALE, y * TILE_SZ*SCALE,
			                TILE_SZ*SCALE, TILE_SZ*SCALE };
		
		SDL_RenderCopy( win_getRenderer( win ), tile_tex,
				&tile_pos, &screen_pos );
	}
}

static void _draw_tilemap( struct Window* win, struct Tilemap* tm, 
                           uint2d_t offset, uint2d_t dims )
{
	for ( unsigned int x = 0; x < dims.x; x++ )
	{
                for ( unsigned int y = 0; y < dims.y; y++ )
		{
                        uint2d_t pos = { x, y }; 
                        _draw_tile( win, tm_getTile( tm, pos ), 
                                    x+offset.x, y+offset.y );
		}
	}
}

void _draw_room( struct Window* win, struct Room* room )
{
        for ( uint8_t i = 0; i < 3; i++ )
        {
                _draw_tilemap( win, room_getTilemap( room, i), 
                               room_getPos( room ),
                               room_getDims( room ) );
        }
}

void _draw_text( struct Window* win, struct Text* text )
{
        char* message = text_getMsg( text );
        struct ImgTex* textset = win_getAsset( win, 1 );
        SDL_Texture* texttex = imgtex_getTex( textset );
        for ( int i = 0; i < strlen( message ); i++ )
        {
                //TODO: copy over dq_item->pos
                int x = i;
                int y = 0;
                SDL_Rect char_pos = imgtex_getTilePos( textset, 
                                                       (int)message[i] - 32 );
                fprintf( stderr, "(%d,%d): %c\n", char_pos.x, char_pos.y, message[i] );
		SDL_Rect screen_pos = { x * SCALE, y * SCALE,
			                TEXT_SZ * SCALE, TEXT_SZ * SCALE };

		SDL_RenderCopy( win_getRenderer( win ), texttex,
				&char_pos, &screen_pos ); 
        }
}
