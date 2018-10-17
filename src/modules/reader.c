#include "../interfaces/reader.h"
#include "../types/synchronized_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void flushInput();

int main(int argc, char **argv) {
  // Queue *q = CreateStringQueue(10);
  feedInput(NULL, 10);
}

/** @override */
void feedInput(Queue *q, int buffSize) {
  char *buff = malloc(sizeof(char) * buffSize);
  int charCount = 0;
  int lineCount = 0;

  while(1) {
    char c = getchar();
    buff[charCount] = c;
    charCount++;
    if (c == '\n') {
       // TODO enqueue string
      printf("line %d: %s", lineCount, buff);
      free(buff);
      buff = malloc(sizeof(char) * buffSize);
      lineCount++;
      charCount = 0;
    } else if (c == EOF) {
      printf("line %d: %s", lineCount, buff);
      break;
    }
    
    if(charCount == buffSize) {
      printf("Input too long, flushing buffer\n");
      flushInput();
      charCount = 0;
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

