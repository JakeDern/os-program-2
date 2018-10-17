#include "../types/synchronized_queue.h"
#include <stdio.h>
#include <stdlib.h>


extern void writeStrings(Queue *q) {
	char* string;

	while (1) {
		string = DequeueString(q);
		printf("%s\n", string);
		free(string);
	}
}


