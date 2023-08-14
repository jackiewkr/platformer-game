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

#include <stdio.h>

#include "libs/draw.h"
#include "libs/events.h"
#include "libs/state.h"
#include "libs/actor.h"
#include "libs/tilemap.h"

int main()
{
        /* Load test actor */
        struct Actor* ac = ac_construct( 1, 32, 16, 32, 8, 16 );
        struct State* gamestate = st_construct();
        /* Load test level */
        st_set_tm(gamestate, tm_populate( "levels/test.lvl" ), 0);
        st_add_ac( gamestate, ac );
        struct Window* win = win_construct();
        struct Event* ev = ev_construct( win );

        /* Main game loop */
        unsigned int close = 0;
        unsigned int redraw = 0;
        while ( !close )
        {
                /* Handle events */
                switch( get_event( ev ) )
                {
                case EVENT_CLOSE:
                        close++;
                        break;
                case EVENT_TICK:
                        redraw++;
                        break;
                default: break;
                }

                /* Handle keyboard input */
                if ( is_key_pressed( ev, KEY_LEFT ) ) st_moveLeft(gamestate);
                if ( is_key_pressed( ev, KEY_RIGHT ) ) st_moveRight(gamestate);
                
                /* Handle drawign and game ticks */
                if (redraw && is_event_queue_clear( ev ) )
                {
                        redraw = 0;
                        win_draw( win, gamestate );
                        st_tick_actors( gamestate );
                }
        }

        st_destruct( gamestate );
        ev_destruct( ev );
        win_destruct( win );
}
