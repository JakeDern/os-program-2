/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#ifndef _READER
#define _READER

#include <stdio.h>
#include "./synchronized_queue.h"

/**
 * Instructs the reader to begin feeding line information
 * from stdin to the first queue. Will reject any input
 * larger than the buffer size and print an error message
 *
 * @param q queue to feed data to 
**/
// TODO: figure out return type
extern void feedInput(Queue *q, int buffSize);

#endif