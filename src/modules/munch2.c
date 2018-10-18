#include "../interfaces/munch2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// int main(int argc, char **argv) {
//         munchTwo(NULL, NULL);
//         return 0;
// }

void munchTwo(Queue *in, Queue *out ) {
	while (1) {
		char *string = DequeueString(in);
		if (string == NULL) {
			// TODO pthread exit
			EnqueueString(out, NULL);
			break;
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









