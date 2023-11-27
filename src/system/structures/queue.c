/**
 * queue.c
 * ===========
 * Dynamic queue implemented as a linked list.
 * 
 * By Jacqueline W.
 **/

#include "queue.h"
#include "../events/error-handler.h"

#include <stdlib.h>

struct Node
{
        struct Node* next;
        void* item;
};

struct Queue
{
        struct Node* head;
        unsigned int size;
};

struct Queue* queue_init( void )
{
        struct Queue* q = malloc( sizeof(struct Queue) );
        if ( q == NULL )
        {
                err_report( FATAL, "Queue failed to malloc()!" );
        }

        q->head = NULL;
        q->size = 0;

        return q;
}

void queue_free( struct Queue* q )
{
        if ( q != NULL )
        {
                //traverse thru list and free each node from head to tail
                struct Node* next_node = q->head;
                while ( next_node != NULL )
                {
                        struct Node* curr_node = next_node;
                        next_node = curr_node->next;

                        free( curr_node );
                }

                free( q );
        }
}

void queue_add( struct Queue* q, void* item )
{
        if ( q->head == NULL )
        {
                q->head = malloc( sizeof(struct Node) );
                q->head->next = NULL;
                q->head->item = item;
        } else
        {
                //traverse to end element
                struct Node* next_node = q->head;
                while ( next_node->next != NULL )
                {
                        next_node = next_node->next;
                }

                next_node->next = malloc( sizeof(struct Node) );
                next_node->next->next = NULL;
                next_node->next->item = item;
        }

        q->size++;
}

void* queue_get( struct Queue* q )
{
        struct Node* head = q->head;
        if ( head != NULL )
        {
                q->head = head->next;
                q->size--;

                void* retval = head->item;

                free( head );
                return retval;
        }
        return head; //returns NULL
}

unsigned int queue_getSize( struct Queue* q )
{
        return q->size;
}
