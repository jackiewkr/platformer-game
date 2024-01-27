#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdint.h>

/**
 * \file window.h
 * \brief Functions for the Window.
 *
 * Functions to do with creating, closing and drawing things to a screen.
 */

/**
 * \def WINDOW_W
 * The width of the window
 *
 * \def WINDOW_H
 * The height of the window
 */

#define WINDOW_W ( 640 )
#define WINDOW_H ( 480 )

/**
 * \struct Window
 * \brief Stores the information needed for the window
 * Wrapper for SDL2's window and renderer, along with event handler
 */
struct Window;

/**
 * \fn struct Window* window_init( void )
 * \brief Initialise a Window struct.
 *
 * Initialises a Window struct with dimensions WINDOW_W x WINDOW_H. Returns
 * a non-NULL ptr on success, NULL on error. 
 */
struct Window* window_init( void );

/**
 * \fn int8_t window_free( struct Window* win )
 * \brief Free the Window struct and associated structs.
 *
 * Frees SDL2's window and renderer and calls SDL_Quit(). Only call this
 * function once every other component has been free()'d. Returns 1 on
 * success, 0 on failure (i.e. if win is NULL).
 *
 * \param win Pointer to an initialised Window struct.
 */
uint8_t window_free( struct Window* win );

/**
 * \fn uint8_t window_shouldClose( struct Window* win )
 * \brief Checks if the window should close.
 *
 * If SDL received a SIGTERM, returns 1, else 0.
 * \param win Pointer to an initialised Window struct.
 */
uint8_t window_shouldClose( struct Window* win );

/**
 * \fn int8_t window_refresh( struct Window* win )
 * \brief Refreshes the screen with new data.
 *
 * Not implemented yet!
 * \param win Pointer to an initialised Window struct.
 */ 
void window_refresh( struct Window* win );

#endif
