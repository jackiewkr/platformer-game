#ifndef GLFW_WRAPPER_H_
#define GLFW_WRAPPER_H_
/**
 * glfw_wrapper.h
 * ==============
 * Wrapper for GLFW to abstract most of the functionality behind a Window
 * struct.
 *
 * By Jacqueline W.
 * Licensed under the Mozilla MPLv2
 **/

struct Window;

/*
 * win_init()
 * ==========
 * Initializes a new GLFW Window.
 *
 * On success, returns an assigned struct Window ptr, else NULL.
 * Any details on errors are printed to stderr and errno is set to a suitable
 * value.
 */
struct Window* win_init();

/*
 * win_free()
 * ==========
 * Frees any memory associated with a Window object.
 *
 * Any details on errors are printed to stderr and errno is set to a suitable
 * value.
 */
void win_free( struct Window* win );

/*
 * win_checkCloseState()
 * =====================
 * Checks if the window's close flag is set to true. The close flag is set by
 * the user trying to close the window, i.e. MOD+SHIFT+Q
 *
 * Returns 1 on window should close, 0 on window shouldn't close
 */
int win_checkCloseState( struct Window* win );

void win_flip( struct Window* win );

#endif
