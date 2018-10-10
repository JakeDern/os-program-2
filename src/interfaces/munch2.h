#ifndef _MUNCHTWO
#define _MUNCHTWO

#include "../types/synchronized_queue.h";

/**
 * Begins processing strings from the incoming queue
 * and feeding them into the outgoing queue for 
 * continuous processing
 *
 * @param in pointer to the queue holding incoming data
 * @param out where to put processed strings
**/
extern void munchTwo(Queue *in, Queue *out);

#endif