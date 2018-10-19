/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#include "../interfaces/reader.h"
#include "../types/synchronized_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void flushInput();

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
      fprintf(stderr, "Input too long, flushing stdin and continuing \n");
      while ( (c = getchar()) != '\n' && c != EOF) {}
      if (c == EOF) {
        free(buff); 
        break;
      }
      charCount = 0;

      // free buff and allocate new string
      free(buff);
      if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
    } else {
      buff[charCount - 1] = c;
      // newline indicates more strings to come
      if(c == '\n') {
        buff[charCount] = '\0';
        EnqueueString(q, buff);
        charCount = 0;
        lineCount++;
        if ( (buff = malloc(sizeof(char) * buffSize)) == NULL ) { exit(1); }
      // EOF indicates no more strings
      } else if (c == EOF) {
        buff[charCount - 1] = '\0';
        EnqueueString(q, buff);
        break;
      }
    }
  }
  EnqueueString(q, NULL);
  pthread_exit(0);
}

