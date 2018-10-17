#include "../interfaces/reader.h"
#include "../types/synchronized_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void flushInput();

// int main(int argc, char **argv) {
//   // Queue *q = CreateStringQueue(10);
//   feedInput(NULL, 10);
// }

/** @override */
void feedInput(Queue *q, int buffSize) {
  char *buff;
  if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
  int charCount = 0;
  int lineCount = 0;

  while(1) {
    char c = getchar();
    charCount++;

    // no room left
    if(charCount == buffSize) {
      // flush input
      printf("Input too long, flushing stdin \n");
      while ( (c = getchar()) != '\n' && c != EOF) {}
      if (c == EOF) { break; }
      charCount = 0;

      // free buff and allocate new string
      free(buff);
      if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
    } else {
      buff[charCount - 1] = c;
      // newline indicates more strings to come
      if(c == '\n') {
        buff[charCount] = '\0';
        printf("line %d: %s", lineCount, buff);
        // TODO enqueue
        charCount = 0;
        lineCount++;

        free(buff);
        if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
      // EOF indicates no more strings
      } else if (c == EOF) {
        // TODO decide to overrite EOF with null terminator, or
        // include it in the string
        buff[charCount] = '\0';
        printf("line %d: %s\n", lineCount, buff);

        free(buff);
        break;
      }
    }
  }
  // TODO enque null pointer
}

