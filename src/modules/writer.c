/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#include "../types/synchronized_queue.h"
#include <stdio.h>
#include <stdlib.h>

/** @override */
void writeStrings(Queue *q) {
	char* string;
	while (1) {
		string = DequeueString(q);

		if(string == NULL) {
			pthread_exit(0);
		}

		printf("%s\n", string);
		free(string);
	}
}
