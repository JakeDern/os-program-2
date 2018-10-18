#include "../interfaces/munch1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** @override */
void munchOne(Queue *in, Queue *out) {
  while (1) {
    char *next = DequeueString(in);
    if (next == NULL) {
      EnqueueString(out, NULL);
      pthread_exit(0);
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