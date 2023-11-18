/**
 * drawqueue.c
 * ===========
 * Simple dynamic array acting as a queue.
 **/

#include "../system.h"

#include <stdlib.h>
#include <string.h>

struct Queue
{
        void** queue;
	unsigned int sz;
};

struct Queue* dq_init()
{
	struct Queue* dq = malloc( sizeof(struct Queue) );
	if ( dq == NULL )
		err_report( FATAL, "Drawqueue failed to malloc()!" );

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
		err_report( FATAL, "Drawqueue failed to realloc!" );
        	
	dq->queue[dq->sz - 1] = item;
}

void* dq_get( struct Queue* dq )
{
        void* item = dq->queue[0];

	memmove( dq->queue[0], dq->queue[1], sizeof(void*) * ( --dq->sz ) );

	return item;
}

unsigned int dq_getSz( struct Queue* dq )
{
        return dq->sz;
}
