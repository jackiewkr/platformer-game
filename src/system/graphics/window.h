#ifndef WINDOW_H_
#define WINDOW_H_

#include "../structures/vectors.h"

/* window.h
 * ========
 * Header for Window struct.
 * Uses GRAPHICS_NS for 'protected' functions. If in graphics namespace, define
 * GRAPHICS_NS before including.
 */

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

#include "imgtex.h"

void* win_getRenderer( struct Window* );
struct ImgTex* win_getAsset( struct Window*, uint8_t index );

#endif
