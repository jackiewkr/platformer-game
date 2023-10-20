/**
 * main.c
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

unsigned int should_quit = 0;

void quit_callback( struct Event* ev );

int main()
{
        struct Window* win = win_init();
	struct Tilemap* tm = tm_populate( "levels/test.lvl" );

	//register evnt callbacks
	ev_setCallback( quit_callback, QUIT );

        while ( !should_quit )
        {
                /* Main loop */
		win_addToDQ( win, tm, TILEMAP_TYPE );
                win_drawFrame( win );
		win_flip( win );
		
		ev_doEvents();
        }
        err_report( INFO, "Closing..." );
        win_free( win );
	
	return 0;
}

void quit_callback( struct Event* ev )
{
	should_quit = 1;
}
