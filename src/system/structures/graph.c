#include <stdlib.h>
#include <stdint.h>

#include "graph.h"

struct Node
{
	uint8_t id;
	struct Node** edge_arr;
	uint8_t edge_arr_sz;

};

static struct Node* _n_init( uint8_t id )
{
	struct Node* n = malloc( sizeof(struct Node) );
	if ( n == NULL )
		err_report( FATAL, "Node failed to malloc()!" );

	n->id = id;
	n->edge_arr = NULL;
	n->edge_arr_sz = 0;

	return n;
}

static void _n_free( struct Node* n )
{
	free( n->edge_arr );
	free( n );
}

static void _n_addConn( struct Node* src, struct Node* dest )
{
	src->edge_arr = realloc( src->edge_arr, 
				 sizeof(struct Node*) * ++src->edge_arr_sz );
	src->edge_arr[src->edge_arr_sz - 1] = dest;
}

struct Graph
{
	struct Node** node_arr;		//associative array
};

struct Graph* g_init()
{
	struct Graph* g = malloc( sizeof(struct Graph) );
	if ( g == NULL )
		err_report( FATAL, "Graph failed to malloc()!" );

	g->node_arr = malloc( sizeof( struct Node* ) * 255 );
	for ( int i = 0; i < 255; i++ )
		g->node_arr[i] = NULL;
}

void g_free( struct Graph* g )
{
	for ( int i = 0; i < 255; i++ )
		_n_free(g->node_arr[i]);
	free( g->node_arr );
	free( g );
}

void g_addNode( struct Graph* g, uint8_t id )
{
	g->node_arr[id] = _n_init( id );
}

void g_addConn( struct Graph* g, uint8_t src_id, uint8_t dest_id )
{
	_n_addConn( g->node_arr[src_id], g->node_arr[dest_id] );
	_n_addConn( g->node_arr[dest_id], g->node_arr[srd_id] );
}

uint8_t* g_getConns( struct Graph* g, uint8_t src )
{
	int i = 0
	uint8_t* arr = NULL;

	struct Node* n = g->node_arr[src];
	for ( i = 0; i < n->edge_arr_sz; i++ )
	{
		arr = realloc( arr, sizeof(uint8_t) * i );
		arr[i] = n->edge_arr[i]->id;
	}

	arr = realloc( arr, sizeof(uint8_t) * (i+1) );
	arr[i] = 0;

	return arr;
}


