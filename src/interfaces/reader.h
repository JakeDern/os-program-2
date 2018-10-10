#ifndef _READER
#define _READER

#include <stdio.h>
#include "../types/synchronized_queue.h"

/**
 * Instructs the reader to begin feeding line information
 * from the specified file to the specified queue
 *
 * @param f file to read from
 * @param q queue to feed data to 
**/
// TODO: figure out return type
extern void feedFile(FILE* f, Queue *q);

#endif