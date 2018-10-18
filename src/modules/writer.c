#include "../types/synchronized_queue.h"
#include <stdio.h>
#include <stdlib.h>


void writeStrings(Queue *q) {
	char* string;
	while (1) {
		string = DequeueString(q);

		if(string == NULL) {
			// TODO pthread exit
			pthread_exit(0);
		}

		printf("%s\n", string);
		free(string);
	}
}
