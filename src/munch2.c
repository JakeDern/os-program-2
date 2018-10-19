/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#include ".//munch2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** @override */
void munchTwo(Queue *in, Queue *out ) {
	while (1) {
		char *string = DequeueString(in);
		if (string == NULL) {
			EnqueueString(out, NULL);
			pthread_exit(0);
		}
		
		int idx = 0;
		char c;
		while ( (c = string[idx]) != '\0') {
			string[idx] = (char)toupper(c);
			idx++;
		}
		EnqueueString(out, string);
	}
}









