#include "../interfaces/munch1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  munchOne(NULL, NULL);
}

void munchOne(Queue *in, Queue *out) {
  char *str = malloc(30);
  strcpy(str, "my string with spaces");

  if(str == NULL) {
    // TODO p_thread_exit
  }

  int strSize = strlen(str);
  for (int i = 0; i < strSize; i++) {
    if (str[i] == ' ') {
      str[i] = '*';
    }
  }
  printf("%s\n", str);
}