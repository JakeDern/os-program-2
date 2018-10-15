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
  char buff[buffSize];
  int count = 0;
  while(fgets(buff, buffSize, stdin) != NULL) {
    int strSize = strlen(buff);
    if (buff[strSize - 1] != '\n' && buff[strSize-1] != EOF) {
      flushInput();
      perror("input exceeded buffer size");
      continue;
    }
    // TODO enqueue string
    printf("line %d:, %s", count, buff);
    count++;
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

