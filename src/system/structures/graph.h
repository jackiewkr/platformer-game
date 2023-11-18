#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdint.h>

struct Graph;

struct Graph g_init( void );

void g_free( struct Graph* );

void g_addNode( struct Graph*, uint8_t id );

void g_addConn( struct Graph*, uint8_t src_id, uint8_t dest_id );

uint8_t* g_getConns( struct Graph*, uint8_t id );

#endif //GRAPH_H_
