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

#include "system/system.h"
#include "level/level.h"

#define LEVELEDIT ( 1 )

unsigned int should_quit = 0;
unsigned int do_place = 0;
uint2d_t cursor = { 0, 0 };
unsigned int tile_type = 0;
char prompt_buf[32] = "";
unsigned int pbuf_sz = 0;

void quit_callback( struct Event* ev )
{
	should_quit = 1;
}

void keyup_callback( struct Event* ev )
{
	enum Keycode key = ev_getKeycode( ev );
	switch ( key )
	{
	case KEY_UP:
		cursor.y -= 1;
		break;
	case KEY_DOWN:
		cursor.y += 1;
		break;
	case KEY_LEFT:
		cursor.x -= 1;
		break;
	case KEY_RIGHT:
		cursor.x += 1;
		break;
        case KEY_ENTER:
		do_place = 1;
		break;
        case KEY_TAB:
		tile_type++;
		break;
        case KEY_A:
        case KEY_B:
        case KEY_C:
        case KEY_D:
        case KEY_E:
        case KEY_F:
        case KEY_G:
        case KEY_H:
        case KEY_I:
        case KEY_J:
        case KEY_K:
        case KEY_L:
        case KEY_M:
        case KEY_N:
        case KEY_O:
        case KEY_P:
        case KEY_Q:
        case KEY_R:
        case KEY_S:
        case KEY_T:
        case KEY_U:
        case KEY_V:
        case KEY_W:
        case KEY_X:
        case KEY_Y:
        case KEY_Z:
                err_report( INFO, "Got Here!" );
                if ( pbuf_sz < 31 )
                {
                        prompt_buf[pbuf_sz++] = (char) (65 + key - 10);
                }
                break;
	default:
		break;
        }

	if ( cursor.x < 0 || cursor.x > 19 )
	{
		cursor.x = 0;
	}
	if ( cursor.y < 0 || cursor.y > 14 )
	{
		cursor.y = 0;
	}
	if ( tile_type > 8 )
		tile_type = 0;
}

int main()
{
        struct Window* win = win_init();
        
	struct Level* lvl = level_createBlank();

        ev_setCallback( quit_callback, QUIT );
	ev_setCallback( keyup_callback, KEYUP );
	
        while ( !should_quit )
        {
                /* Main loop */
                struct Text* text = text_init( prompt_buf, pbuf_sz );
                uint2d_t pos = {0,0};
		win_addToQueue( win, ROOM_TYPE, lvl, pos );
                win_addToQueue( win, TEXT_TYPE, text, pos );
		win_drawFrame( win );
		win_drawCursor( win, cursor );
		win_flip( win );

		ev_doEvents();
        }
        err_report( INFO, "Closing..." );
        level_free( lvl );
        win_free( win );
	return 0;
}


