/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */

#include "./synchronized_queue.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int nextIndex(int currIdx, int size);
int isEmpty(Queue *q);
int isFull(Queue *q);
int getSize(Queue *q);
void printQueue(Queue *q);

/** @override */
Queue * CreateStringQueue(int size) {
  // TODO sanity check on size
  Queue *q;
  if ( (q = malloc(sizeof(Queue))) == NULL ) {
      perror("\n");
      exit(1);
  }
  if ( (q->items = malloc(sizeof(char*) * size)) == NULL ) {
      perror("\n");
      exit(1);
  }
  q->head = 0;
  q->tail = 0;
  q->size = size;
  q->numItems = 0;
  q->enqueueCount = 0;
  q->dequeueBlockCount = 0;
  q->dequeueCount = 0;
  q->enqueueBlockCount = 0;

  if ( ((q->mutex = malloc(sizeof(pthread_mutex_t))) == NULL)
    || ((q->enqueueLine = malloc(sizeof(pthread_cond_t))) == NULL)
    || ((q->dequeueLine = malloc(sizeof(pthread_cond_t))) == NULL) ) {
    perror("\n");
    exit(1);
  }
  
  pthread_mutex_init(q->mutex, NULL);
  pthread_cond_init(q->enqueueLine, NULL);
  pthread_cond_init(q->dequeueLine, NULL);
  
  // TODO init mutex and cond vars
  return q;
}

/** @override */
void EnqueueString(Queue *q, char *string) {
  // grab the lock and block if full
  pthread_mutex_lock((q->mutex));
  if (isFull(q)) {
    (q->enqueueBlockCount)++;
    pthread_cond_wait((q->enqueueLine), (q->mutex));
  }

  //Enqueue
  if (isEmpty(q)) {
    (q->items)[q->head] = string;
  } else {
    int tailIdx = nextIndex(q->tail, q->size);
    (q->items)[tailIdx] = string;
    q->tail = tailIdx;
  }

  // inc items and log enqueue
  (q->numItems)++;
  (q->enqueueCount)++;

  // notify dequeue and free the lock
  pthread_cond_signal((q->dequeueLine));
  pthread_mutex_unlock((q->mutex));
}

/** @override */
char * DequeueString(Queue *q) {
  // grab lock and block if empty
  pthread_mutex_lock((q->mutex));
  if (isEmpty(q)) {
    (q->dequeueBlockCount)++;
    pthread_cond_wait((q->dequeueLine), (q->mutex));
  }

  // remove string
  int headIdx = (getSize(q) == 1) ? q->head : nextIndex(q->head, q->size);
  char *string = (q->items)[q->head];
  (q->numItems)--;
  (q->dequeueCount)++;

  // null out pointer
  (q->items)[q->head] = NULL;
  q->head = headIdx;

  // signal enqueue and free the lock
  pthread_cond_signal((q->enqueueLine));
  pthread_mutex_unlock((q->mutex));

  return string;
}

/** @override */
void PrintQueueStats(Queue *q) {
  pthread_mutex_lock((q->mutex));
  fprintf(stderr, "Enqueues: %d, Dequeues: %d, Enqueue Blocks: %d, Dequeue Blocks: %d\n",
      q->enqueueCount, q->dequeueCount, q->enqueueBlockCount, q->dequeueBlockCount);
  pthread_mutex_unlock((q->mutex));
}

void printQueue(Queue *q) {
  // TODO remove
  pthread_mutex_lock((q->mutex));
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
  pthread_mutex_unlock((q->mutex));
}

/** @override */
void FreeQueue(Queue *q) {
  free(q->items);
  pthread_mutex_destroy((q->mutex));
  free(q);
}


/**
 * Calculates and returns the number of items in this
 * queue
 * */
int getSize(Queue *q) {
  return q->numItems;
}

/**
 * Determines if the provided queue is empty
 * 
 * @return 1 if and only if this queue is empty, 0 otherwise
 * */
int isEmpty(Queue *q) {
 return q->numItems == 0;
}


/**
 * Determines if the provided queue is full
 * 
 * @return 1 if and only if this queue is full, 0 otherwise
 * */
int isFull(Queue *q) {
  return q->numItems == q->size;
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

