#include <allegro5/allegro.h>
#include <time.h>

#include "events.h"
#include "draw.h"
#include "constants.h"
#include "point.h"

struct Event
{
	ALLEGRO_EVENT_QUEUE* event_queue;
        ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT event;
        unsigned short int keys_pressed;
};

struct Event* ev_construct( struct Window* win )
{
        struct Event* ev = malloc( sizeof(struct Event) );
        ev->keys_pressed = 0;
        
        ev->timer = al_create_timer( 1.0 / FPS );
        ev->event_queue = al_create_event_queue();

        /* register event sources */
        al_register_event_source( ev->event_queue,
                                  al_get_keyboard_event_source() );
        al_register_event_source( ev->event_queue,
                                  al_get_display_event_source(
                                          (ALLEGRO_DISPLAY*)
                                          win_getDisp( win )
                                  ) );
        al_register_event_source( ev->event_queue,
                                  al_get_timer_event_source(ev->timer) );
        al_register_event_source( ev->event_queue,
                                  al_get_mouse_event_source() );

        al_start_timer( ev->timer );

        return ev;
}

void ev_destruct( struct Event* ev )
{
        al_destroy_timer( ev->timer );
        al_destroy_event_queue( ev->event_queue );

        free( ev );
}

/* Toggles key pressed state for each key */
static void handle_key_event( struct Event* ev, int keycode )
{
        switch ( keycode )
        {
        case ALLEGRO_KEY_LEFT:
                ev->keys_pressed ^= 1;
                break;
        case ALLEGRO_KEY_RIGHT:
                ev->keys_pressed ^= 2;
                break;
        case ALLEGRO_KEY_UP:
                ev->keys_pressed ^= 4;
                break;
        case ALLEGRO_KEY_DOWN:
                ev->keys_pressed ^= 8;
                break;
        default: break;
        }
}

unsigned int get_event( struct Event* ev )
{
        al_wait_for_event( ev->event_queue, &ev->event );

	if ( ev->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
		return EVENT_CLOSE;
	if ( ev->event.type == ALLEGRO_EVENT_TIMER )
		return EVENT_TICK;
	if ( ev->event.type == ALLEGRO_EVENT_KEY_DOWN ||
             ev->event.type == ALLEGRO_EVENT_KEY_UP )
		handle_key_event( ev, ev->event.keyboard.keycode );
	if ( ev->event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
		return EVENT_MOUSE;
	return NO_EVENT;
}

unsigned int is_event_queue_clear( struct Event* ev )
{
        if ( al_is_event_queue_empty( ev->event_queue ) )
		return 1;
	return 0;
}

/*
 * int parse_event_key:
 * If the current event is a EVENT_KEY, returns the keycode pressed.
 */
int parse_event_key( struct Event* ev )
{
        return ev->event.keyboard.keycode;
}

unsigned int is_key_pressed( struct Event* ev, int key_enum )
{
        return ev->keys_pressed & key_enum;
}

int parse_event_mouse_button( struct Event* ev )
{
        return ev->event.mouse.button;
}

struct Point parse_event_mouse_axes( struct Event* ev )
{
        return pnt_init( ev->event.mouse.x, ev->event.mouse.y, 0 );
}
