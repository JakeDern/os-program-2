#ifndef _WRITER
#define _WRITER

#include <stdio.h>
#include "../types/synchronized_queue.h"

/**
 * Instructs the writer to begin writing strings to
 * the provided output file, as they become available
 * in the queue
 *
 * @param f the file to write to
 * @param q the queue which holds the strings 
**/
// TODO determine what this return type should be
extern void writeStrings(Queue *q);

#endif
