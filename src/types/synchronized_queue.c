#include "./synchronized_queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int nextIndex(int currIdx, int size);
int isEmpty(Queue *q);
int isFull(Queue *q);
int getSize(Queue *q);
void printQueue(Queue *q);

int main(int argc, char **argv) {
  Queue *q = CreateStringQueue(10);
  char *s = malloc(3);
  strcpy(s, "aa");
  EnqueueString(q, s);

  for(int i = 0; i < 9; i++) {
    EnqueueString(q, "bb");
    printQueue(q);
  }

  printf("\n");
  PrintQueueStats(q);
  printf("\n");

  for(int i = 0; i < 4; i++) {
    DequeueString(q);
    printQueue(q);
  }

  printf("\n");
  PrintQueueStats(q);
  printf("\n");

  for (int i = 0; i < 4; i++) {
    EnqueueString(q, "cc");
    printQueue(q);
  }

  printf("\n");
  PrintQueueStats(q);
  printf("\n");

  while(!isEmpty(q)) {
    DequeueString(q);
    printQueue(q);
  }

  printf("\n");
  PrintQueueStats(q);
  printf("\n");

  PrintQueueStats(q);

  return 0;
}

/** @override */
Queue * CreateStringQueue(int size) {
  // TODO sanity check on size
  Queue *q = malloc(sizeof(Queue));
  q->items = malloc(sizeof(char*) * size);
  q->head = 0;
  q->tail = 0;
  q->size = size;
  return q;
}

/** @override */
void EnqueueString(Queue *q, char *string) {
  // TODO mutual exclusion
  if (isFull(q)) {
    printf("ERROR enqueue on full queue\n");
    exit(1);
  }

  //Enqueue
  if (isEmpty(q)) {
    (q->items)[0] = string;
  } else {
    int tailIdx = nextIndex(q->tail, q->size);
    (q->items)[tailIdx] = string;
    q->tail = tailIdx;
  }
}

/** @override */
char * DequeueString(Queue *q) {
  // TODO mutual exclusion
  if (isEmpty(q)) {
    printf("ERROR dequeue on empty queue\n");
    exit(1);
  }

  // remove string
  int headIdx = (getSize(q) == 1) ? q->head : nextIndex(q->head, q->size);
  char *string = (q->items)[q->head];

  // null out pointer
  (q->items)[q->head] = NULL;
  q->head = headIdx;

  return string;
}

/** @override */
void PrintQueueStats(Queue *q) {
  // TODO mutual exclusion
  // TODO implement
  printf("First item: %s, head: %d, tail: %d, size: %d\n",
      (q->items)[0], q->head, q->tail, getSize(q));
}

void printQueue(Queue *q) {
  int size = q->size;
  char **items = q->items;
  printf("[ ");
  for (int i = 0; i < size; i++) {
    char *next = items[i];
    if (next) {
      printf("  %s  ", next);
    } else {
      printf("%s", next);
    }
    if (i != size -1) {
      printf(",");
    }
  }
  printf("]\n");
}

/** @override */
void FreeQueue(Queue *q) {
  // TODO mutual exclusion
  free(q->items);
  free(q);
}


/**
 * Calculates and returns the number of items in this
 * queue
 * */
int getSize(Queue *q) {
  // TODO mutual exclusion
  int headIdx = q->head;
  int tailIdx = q->tail;
  int size = q->size;

  if (isEmpty(q)) return 0;

  int diff = headIdx - tailIdx;
  return (diff <= 0) ? ((-1 * diff) + 1) : ((size - diff) + 1);
}

/**
 * Determines if the provided queue is empty
 * 
 * @return 1 if and only if this queue is empty, 0 otherwise
 * */
int isEmpty(Queue *q) {
  // TODO mutual exclusion
  int head = q->head;
  char *headString = (q->items)[head];

  return headString == NULL;
}


/**
 * Determines if the provided queue is full
 * 
 * @return 1 if and only if this queue is full, 0 otherwise
 * */
int isFull(Queue *q) {
  // TODO mutual exclusion
  int tail = q->tail;
  int head = q->head;
  int size = q->size;
  return nextIndex(tail, size) == head;
}

/**
 * Calculates the next index of either the head or
 * tail based on the starting index. 
 * 
 * note: does nothing determine if the queue is full/empty
 * 
 * @param currIdx the current index of the head or tail
 * @param size the size of the array underneath the queue
 * */
int nextIndex(int currIdx, int size) {
  return (currIdx + 1 == size) ? 0 : currIdx + 1;
}

