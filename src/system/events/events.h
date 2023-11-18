#ifndef EVENTS_H_
#define EVENTS_H_

#include "keycodes.h" //struct Keycode definition

struct Event;

enum EventType
{
        QUIT,
        MOUSEMOVE,
        MOUSEUP,
        MOUSEDOWN,
        KEYDOWN,
        KEYUP
};

//func ptr; takes struct Event, returns void
typedef void (*event_callback_t) (struct Event*);

/* ev_setCallback()
 * ================
 * Sets the callback function for a given event type. The given event_callback_t
 * value overwrites the set callback function.
 */
void ev_setCallback( event_callback_t, enum EventType );

/* ev_doEvents()
 * =============
 * Executes the callback functions for every event in the event queue until the
 * queue is empty.
 */
void ev_doEvents( void );

/* ev_getKeycode()
 * ===============
 * Gets the current keycode of the given Event if it is a KEYUP or KEYDOWN
 * event. Returns an enum Keycode representing the current key pressed or 
 * released.
 */
enum Keycode ev_getKeycode( struct Event* );

#endif
