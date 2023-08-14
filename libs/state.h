#ifndef __STATE_H
#define __STATE_H

/**
 * state.h
 * =========
 * Header file for State object. Exposes all public functions for State object.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "tilemap.h"
#include "actor.h"

struct State;

/* Constructor for State object */
struct State* st_construct();

/* Destructor for State object */
void st_destruct( struct State* st );

/** TILEMAP FUNCS **/
/* Set either foreground or background tilemap */
void st_set_tm( struct State* st, struct Tilemap* tm, int fg );
/* Getter for either foreground or background tilemap */
struct Tilemap* st_get_tm( struct State* st, int fg );

/** ACTOR FUNCS **/
/* Adds actor to list of actors in level */
void st_add_ac( struct State* st, struct Actor* ac );

/* Getter for actor in level */
struct Actor* st_get_ac( struct State* st, int index );

/* Called every tick; calls for physics to be done on each active actor */
void st_tick_actors( struct State* st );

/* Fucntions for moving the player */
void st_moveLeft( struct State* st );
void st_moveRight( struct State* st );

#endif //__STATE_H
