#ifndef __ACTOR_H
#define __ACTOR_H

#include "point.h"
#include "tilemap.h"

struct Actor;

/**
 * Actor types:
 * 0 - Player
 * 1 - Enemy
 * 2 - Moving object
 * 3 - Interactable areas
 **/
struct Actor* ac_construct( int type, int x, int y, int z, int w, int h );

void ac_destruct( struct Actor* ac );

void ac_tick( struct Actor* ac, struct Tilemap* tm );

void ac_deactivate( struct Actor* ac );
void ac_activate( struct Actor* ac );

/* Getters */
struct Point ac_getPos( struct Actor* ac );
int ac_getType( struct Actor* ac );
unsigned int ac_isActive( struct Actor* ac );
int ac_getWidth( struct Actor* ac );
int ac_getHeight( struct Actor* ac );

/* Setters */
void ac_setPos( struct Actor* ac );

/* Used for moving player */
void ac_moveLeft( struct Actor* ac );
void ac_moveRight( struct Actor* ac );
void ac_moveUp( struct Actor* ac );
void ac_moveDown( struct Actor* ac );

#endif //__ACTOR_H
