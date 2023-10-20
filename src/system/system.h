#ifndef SYSTEM_H_
#define SYSTEM_H_
/**
 * system.h
 * ========
 * Public functions for all system-related functions and objects.
 * By Jacqueline W.
 **/

/** Helpful Structs **/
#include "structures/vectors.h"

/** Window Funcs **/
struct Window;

/*
 * win_init()
 * ==========
 * Initializes a new SDL Window.
 *
 * On success, returns an assigned struct Window ptr, else NULL.
 * Any details on errors are printed to stderr and errno is set to a suitable
 * value.
 */
struct Window* win_init( void );

/*
 * win_free()
 * ==========
 * Frees any memory associated with a Window object.
 *
 * Any details on errors are printed to stderr and errno is set to a suitable
 * value.
 */
void win_free( struct Window* );

enum ItemType
{
        ROOM_TYPE,
	ENTITY_TYPE,
	TEXT_TYPE,
	IMAGE_TYPE
};

/*
 * win_addToQueue()
 * =============
 * Adds a drawable object to the draw-queue to be drawn next frame at the given
 * position.
 */
void win_addToQueue( struct Window*, enum ItemType, void* item,
		     ui_vec2_t pos );

/*
 * win_drawFrame()
 * ===============
 * Draws everything from the drawqueue to the backbuffer.
 */
void win_drawFrame( struct Window* );

/* win_flip()
 * ==========
 * Renders the backbuffer onto the screen.
 */
void win_flip( struct Window* );

/* win_drawCursor()
 * ================
 * Draws the cursor onto the backbuffer at a given position.
 * [level designer only]
 */
void win_drawCursor( struct Window*, ui_vec2_t );

/** Event Handling **/
struct Event;

enum EventType
{
	QUIT,
	MOUSEMOVE,
	MOUSEDOWN,
	MOUSEUP,
        KEYDOWN,
	KEYUP
};

//function pointer; takes struct Event ptr; returns nothing
typedef void (*event_callback_t) (struct Event*);

/* ev_setCallback()
 * ================
 * Sets the callback function for a given event type. If event_callback_t is
 * NULL then any callback function already set is unset. Will only allow one
 * function to be set to a given event at any time.
 */
void ev_setCallback( event_callback_t, enum EventType );

/* ev_poll()
 * =========
 * Continuously polls the event queue until the event queue is empty.
 */
void ev_doEvents( void );

enum Keys
{
	KEY_NONE,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ENTER,
	KEY_TAB
};

/* ev_getKeycode()
 * ===============
 * Gets the current keycode of the given event. If the event is not KEYDOWN
 * or KEYUP then KEY_NONE is sent. Only checks for a subset of keys.
 */
enum Keys ev_getKeycode( struct Event* );

/** Error Handling **/
enum ErrorLevel
{
        INFO,
        WARNING,
        FATAL
};

/*
 * err_report()
 * ============
 * Reports the current errno and strerror values to stderr along with any
 * specified message.
 */
void err_report( enum ErrorLevel, const char* msg );


#endif
