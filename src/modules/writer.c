/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#include "./synchronized_queue.h"
#include <stdio.h>
#include <stdlib.h>

/** @override */
void writeStrings(Queue *q) {
	int cnt = 0;
	char* string;
	while (1) {
		string = DequeueString(q);

		if(string == NULL) {
			fprintf(stderr, "String processed: %d\n", cnt);
			pthread_exit(0);
		}
		cnt++;
		printf("%s", string);
		free(string);
	}
}
