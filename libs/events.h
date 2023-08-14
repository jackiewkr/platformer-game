#ifndef __EVENTS_H
#define __EVENTS_H

#include <allegro5/allegro.h>

#include "point.h"
#include "draw.h"

struct Event;

enum EventTypes
{
        EVENT_CLOSE,
	EVENT_TICK,
	EVENT_KEY, //deprecated, check for keys separately to events
	EVENT_MOUSE,
	NO_EVENT = 99
};

enum VisibleKeys
{
        KEY_LEFT = 1,
        KEY_RIGHT = 2,
        KEY_UP = 4,
        KEY_DOWN = 8
};

struct Event* ev_construct( struct Window* win );

void ev_destruct( struct Event* ev );

unsigned int get_event( struct Event* ev );

unsigned int is_event_queue_clear( struct Event* ev );

int parse_event_key( struct Event* ev ); //deprecated

struct Point parse_event_mouse_axes( struct Event* ev );

int parse_event_mouse_button( struct Event* ev );

unsigned int is_key_pressed( struct Event* ev, int key );

#endif //__EVENTS_H
