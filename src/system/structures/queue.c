/**
 * queue.c
 * ===========
 * Simple dynamic array acting as a queue.
 **/

#define STRUCTURES_NS

#include "queue.h"
#include "../events/error-handler.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Queue
{
        void** queue;
	unsigned int sz;
};

static void dq_print( struct Queue* q )
{
        for ( int i = 0; i < q->sz; i++ )
        {
                printf( "%s\n", (char*)q->queue[i] );
        }
        printf( "===\n" );
}

struct Queue* dq_init( void )
{
	struct Queue* dq = malloc( sizeof(struct Queue) );
	if ( dq == NULL )
		err_report( FATAL, "Queue failed to malloc()!" );

	dq->sz = 0;
	dq->queue = NULL;

	return dq;
}

void dq_free( struct Queue* dq )
{
        if ( dq->queue != NULL )
		free(dq->queue );

	free( dq );
}

void dq_add( struct Queue* dq, void* item )
{
        dq->queue = realloc( dq->queue, sizeof(void*) * ( ++dq->sz ) );
	if ( dq->queue == NULL )
		err_report( FATAL, "Queue failed to realloc()!" );
        	
	dq->queue[dq->sz - 1] = item;
}

void* dq_get( struct Queue* dq )
{
        dq_print( dq );
        void* item = dq->queue[0];

	memmove( dq->queue[0], dq->queue[1], sizeof(void*) * ( dq->sz - 1 ) );
        dq->sz--;
        dq_print( dq );
	return item;
}

unsigned int dq_getSz( struct Queue* dq )
{
        return dq->sz;
}
