#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "point.h"
#include "tilemap.h"

/**
 * struct Physics_Object
 * ----------
 * Generic object that is affected by physics. 
 */
struct Physics_Obj;

/* Constructor for Physics Object */
struct Physics_Obj* ph_construct( int width, int height );

/* Destructor for Physics Object  */
void ph_destruct( struct Physics_Obj* );

/* Getters */
struct Point ph_get_pos( struct Physics_Obj* pho );

struct Point ph_get_size( struct Physics_Obj* pho );

struct Point ph_get_vel( struct Physics_Obj* pho );

struct Point ph_get_acc( struct Physics_Obj* pho );

/* Setters */
void ph_set_pos( struct Physics_Obj* pho, struct Point p );

void ph_set_vel( struct Physics_Obj* pho, struct Point p, int rel );

void ph_set_acc( struct Physics_Obj* pho, struct Point p );

/* Tick function: called every frame */
void ph_tick( struct Physics_Obj* pho, struct Tilemap* tm );

#endif //__PHYSICS_H
