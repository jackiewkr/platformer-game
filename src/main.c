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

#include "system/system.h"

#include <string.h>

unsigned int should_quit = 0;

void quit_callback( struct Event* ev );

char* indev_1 = "Hello,";
char* indev_2 = "This project is still in the early stages of development.";
char* indev_3 = "Please checkout any 'dev-*' branches for current work";

int main()
{
        struct Window* win = win_init();

        //simple message to display while level editor is being created
	struct Text* t1 = text_init( indev_1, strlen( indev_1 ) );
        uint2d_t t1_pos = { 0,0 };
        struct Text* t2 = text_init( indev_2, strlen( indev_2 ) );
        uint2d_t t2_pos = { 0,1 };
        struct Text* t3 = text_init( indev_3, strlen( indev_3 ) );
        uint2d_t t3_pos = { 0,3 };

	//register event callbacks
	ev_setCallback( quit_callback, QUIT );

        while ( !should_quit )
        {
                /* Main loop */
                
		win_addToQueue( win, TEXT_TYPE, t1, t1_pos );
		win_addToQueue( win, TEXT_TYPE, t2, t2_pos );
		win_addToQueue( win, TEXT_TYPE, t3, t3_pos );
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
