#include "./interfaces/reader.h"
#include "./interfaces/munch1.h"
#include "./interfaces/munch2.h"
#include "./interfaces/writer.h"
#include "./types/synchronized_queue.h"

const int BUFF_SIZE = 1024;
const int QUEUE_SIZE = 10;

void readStart(void *args);
void munchOneStart(void *args);
void munchTwoStart(void *args);
void writeStart(void *args);

typedef struct ThreadParams {
  Queue *qin;
  Queue *qout;
} ThreadParams;

int main(int argc, char **argv) {
  // allocate shared queues
  Queue *readerOut = CreateStringQueue(QUEUE_SIZE);
  Queue *munchOneOut = CreateStringQueue(QUEUE_SIZE);
  Queue *munchTwoOut = CreateStringQueue(QUEUE_SIZE);

  // create params for each thread
  ThreadParams *readerParams, *munchOneParams, *munchTwoParams, *writerParams;
  if ( (readerParams = malloc(sizeof(ThreadParams))) == NULL 
    || (munchOneParams = malloc(sizeof(ThreadParams))) == NULL 
    || (munchTwoParams = malloc(sizeof(ThreadParams))) == NULL 
    || (writerParams = malloc(sizeof(ThreadParams))) == NULL ) {
      perror("");
      exit(1);
    }

  // link up queues
  readerParams->qout = readerOut;
  munchOneParams->qin = readerOut;
  munchOneParams->qout = munchOneOut;
  munchTwoParams->qin = munchOneOut;
  munchTwoParams->qout = munchTwoOut;
  writerParams->qin = munchTwoOut;


  // create threads 
  pthread_t reader, munch1, munch2, writer;
  int readerRet, munch1Ret, munch2Ret, writerRet;
  readerRet = pthread_create(&reader, NULL, &readStart, (void*) readerParams);
  munch1Ret = pthread_create(&munch1, NULL, &munchOneStart, (void*) munchOneParams);
  munch2Ret = pthread_create(&munch2, NULL, &munchTwoStart, (void*) munchTwoParams);
  writerRet = pthread_create(&writer, NULL, &writeStart, (void*) writerParams);

  // wait for all threads to exit
  pthread_join(reader, NULL);
  pthread_join(munch1, NULL);
  pthread_join(munch2, NULL);
  pthread_join(writer, NULL);

  // print stats
  printf("Reader / Munch1 queue:\n");
  PrintQueueStats(readerOut);
  printf("Munch1 / Munch2 queue:\n");
  PrintQueueStats(munchOneOut);
  printf("Munch2 / Writer queue:\n");
  PrintQueueStats(munchTwoOut);
}

void readStart(void *args) {
  ThreadParams *params = (ThreadParams *) args;
  feedInput(params->qout, BUFF_SIZE);
}

void munchOneStart(void *args) {
  ThreadParams *params = (ThreadParams *) args;
  munchOne(params->qin, params->qout);
}

void munchTwoStart(void *args) {
  ThreadParams *params = (ThreadParams *) args;
  munchTwo(params->qin, params->qout);
}

void writeStart(void *args) {
  ThreadParams *params = (ThreadParams *) args;
  writeStrings(params->qin);
}

