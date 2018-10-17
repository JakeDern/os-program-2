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
		printf("Inputed line: %s\n", string);
	
		if (string == NULL) {
			exit(0);
		}
		
		int len	= strlen(string);
		printf("str len: %d\n", len);
		for (int i = 0; i < len; i++) {
			
			string[i] = (char)toupper(string[i]);

		}
		EnqueueString(out, string);
	}
}









