#ifndef __DRAW_H
#define __DRAW_H

#include "state.h"

struct Window;

struct Window* win_construct();

void win_destruct( struct Window* win );

void win_draw( struct Window* win, struct State* s );

void* win_getDisp( struct Window* win );

#endif //__DRAW_H
