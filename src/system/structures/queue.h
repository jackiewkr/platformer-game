#ifndef DRAWQUEUE_H_
#define DRAWQUEUE_H_

struct Queue;

struct Queue* dq_init();

void dq_free( struct Queue* dq );

void dq_add( struct Queue* dq, void* item );

void* dq_get( struct Queue* dq );

unsigned int dq_getSz( struct Queue* dq );

#endif
