#ifndef QUEUE_H_
#define QUEUE_H_

/**
 * queue.h
 * =======
 * Dynamic queue using a linked list. Stores any ptr cast to void*.
 * 
 * By Jacqueline W.
 */

struct Queue;

/* queue_init()
 * ============
 * Initializes a queue with the initial size of 0.
 * Returns a Queue struct ptr on success, NULL on error. Additional info
 * is printed to stderr.
 */
struct Queue* queue_init( void );

/* queue_free()
 * ============
 * Frees any memory used for the Queue struct. Does not free any void* items
 * stored in the queue.
 */
void queue_free( struct Queue* );

/* queue_add()
 * ===========
 * Adds an item to the tail of the queue.
 */
void queue_add( struct Queue*, void* item );

/* queue_get()
 * ===========
 * Gets the item at the head of the queue.
 * Returns void* on success, NULL on error. Additional info is printed to 
 * stderr.
 */
void* queue_get( struct Queue* );

/* queue_getSize()
 * ===============
 * Gets the number of items in the queue.
 */
unsigned int queue_getSize( struct Queue* );

#endif
