/**
 * level-designer.c
 * =========
 * Main file for the platformer game. Handles logic relating to gameticks and
 * calling of functions when needed.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "libs/sdl_wrapper/sdl_wrapper.h"
#include "libs/sdl_wrapper/imgtex.h"
#include "libs/error-handler/error-handler.h"
#include "libs/tilemap.h"
#include "libs/events.h"

#define LEVELEDIT ( 1 )

unsigned int should_quit = 0;
unsigned int do_place = 0;
unsigned int curs_x = 0;
unsigned int curs_y = 0;
unsigned int tile_type = 0;

void quit_callback( struct Event* ev )
{
	should_quit = 1;
}

void keyup_callback( struct Event* ev )
{
	enum Keys key = ev_getKeycode( ev );
	switch ( key )
	{
	case KEY_UP:
		curs_y -= 1;
		break;
	case KEY_DOWN:
		curs_y += 1;
		break;
	case KEY_LEFT:
		curs_x -= 1;
		break;
	case KEY_RIGHT:
		curs_x += 1;
		break;
        case KEY_ENTER:
		do_place = 1;
		break;
        case KEY_TAB:
		tile_type++;
		break;
	default:
		break;
	}

	if ( curs_x < 0 || curs_x > 19 )
	{
		curs_x = 0;
	}
	if ( curs_y < 0 || curs_y > 14 )
	{
		curs_y = 0;
	}
	if ( tile_type > 8 )
		tile_type = 0;
}

int main()
{
        struct Window* win = win_init();
	struct Tilemap* tm = tm_createBlank();

        ev_setCallback( quit_callback, QUIT );
	ev_setCallback( keyup_callback, KEYUP );
	
        while ( !should_quit )
        {
                /* Main loop */
		win_addToDQ( win, tm, TILEMAP_TYPE );
		win_drawFrame( win );
		win_drawCursor( win, curs_x, curs_y );
		win_flip( win );

		ev_doEvents();

		if ( do_place )
		{
			tm_mod_tile( tm, tile_type, curs_x, curs_y );
			do_place = 0;
		}
        }
        err_report( INFO, "Closing..." );
	tm_export( tm, "test.lvl" );
        win_free( win );
	return 0;
}


