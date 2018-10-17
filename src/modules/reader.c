#include "../interfaces/reader.h"
#include "../types/synchronized_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void flushInput();

int main(int argc, char **argv) {
  // Queue *q = CreateStringQueue(10);
  feedInput(NULL, 50);
}

/** @override */
void feedInput(Queue *q, int buffSize) {
  char *buff;
  if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
  int charCount = 0;
  int lineCount = 0;

  while(1) {
    char c = getchar();
    charCount++;

    if(charCount == buffSize + 1) {
      printf("Input too long, flushing stdin \n");
      flushInput();
      charCount = 0;
      free(buff);
      if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
    } else {
      if(c == '\n') {
        buff[charCount] = '\0';
        // Printing out with %s doesnt work
        printf("line %d: %s\n", lineCount, buff);
        // but checking manually, all of the chars are there
        for(int i = 0; i < charCount; i++) {
          printf("%c", buff[i]);
        }
        printf("\n");
        // TODO enqueue
        charCount = 0;
        lineCount++;
        free(buff);
        if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
      } else if (c == EOF) {
        buff[charCount] = '\0';
        printf("line %d: %s\n", lineCount, buff);
        free(buff);
        break;
      } else {
        buff[charCount] = c;
        // printf("%c\n", buff[charCount]);
      }
    }
  }
  // TODO enque null pointer
}

/**
 * Flushes the remaining characters from stdin
 * */
void flushInput() {
  char next;
  while ( (next = getchar()) != '\n' && next != EOF) {}
}

