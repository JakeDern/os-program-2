#include "../interfaces/munch1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// int main(int argc, char **argv) {
//   munchOne(NULL, NULL);
// }

void munchOne(Queue *in, Queue *out) {
  // int strSize = strlen(str);
  // for (int i = 0; i < strSize; i++) {
  //   if (str[i] == ' ') {
  //     str[i] = '*';
  //   }
  // }

  while (1) {
    char *next = DequeueString(in);
    if (next == NULL) {
      // TODO pthread exit
      EnqueueString(out, NULL);
      break;
    }

    int idx = 0;
    char c;
    while ( (c = next[idx]) != '\0') {
      if (c == ' ') {
        next[idx] = '*';
      }
      idx++;
    }
    EnqueueString(out, next);
  }
}