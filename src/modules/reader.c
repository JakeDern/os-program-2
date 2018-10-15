#include "../interfaces/reader.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  feedInput(NULL, 50);
}

void feedInput(Queue *q, int buffSize) {
  char buff[buffSize];
  int count = 0;
  while(fgets(buff, buffSize, stdin) != NULL) {
    printf("line %d: %s", count, buff);
    count++;
  }
}

