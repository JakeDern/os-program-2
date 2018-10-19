/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#ifndef _SYNCQUEUE
#define _SYNCQUEUE

#include <pthread.h>

typedef struct Queue {
    char **items;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    int head;
    int tail;
    int size;
    int numItems;
    pthread_mutex_t *mutex;
    pthread_cond_t *enqueueLine;
    pthread_cond_t *dequeueLine;
    // TODO determine synchronization vars needed for the struct
} Queue;

/**
 * Creates an empty queue of size size
 *
 * @param size the capacity of the desired queue
 * @returns pointer to a new Queue struct or null
 * on failure
**/
extern Queue *CreateStringQueue(int size);

/**
 * Enqueues the provided string if the queue is not
 * full, or blocks until there is room
 * 
 * @param q the queue
 * @param string the string to enqueue
**/
extern void EnqueueString(Queue *q, char *string);

/**
 * Dequeues a string from the provided queue or
 * blocks until a string is available to dequeue
 *
 * @param q the queue
 * @returns char *pointer to the dequeued string
**/
extern char *DequeueString(Queue *q);

/**
 * Prints available statistics about the given
 * queue
 *
 * @param q the queue
**/
extern void PrintQueueStats(Queue *q);

/**
 * Frees all memory associated with the given queue,
 * including its contents.  
**/
extern void FreeQueue(Queue *q);

#endif