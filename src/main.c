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
  printf("start main\n");
  // allocate shared queues
  Queue *readerOut = CreateStringQueue(QUEUE_SIZE);
  Queue *munchOneOut = CreateStringQueue(QUEUE_SIZE);
  Queue *munchTwoOut = CreateStringQueue(QUEUE_SIZE);

  // create params for each thread
  printf("create params\n");
  ThreadParams *readerParams = malloc(sizeof(ThreadParams));
  ThreadParams *munchOneParams = malloc(sizeof(ThreadParams)); 
  ThreadParams *munchTwoParams = malloc(sizeof(ThreadParams)); 
  ThreadParams *writerParams = malloc(sizeof(ThreadParams)); 

  // link up queues
  printf("link queues\n"); 
  readerParams->qout = readerOut;
  munchOneParams->qin = readerOut;
  munchOneParams->qout = munchOneOut;
  munchTwoParams->qin = munchOneOut;
  munchTwoParams->qout = munchTwoOut;
  writerParams->qin = munchTwoOut;


  // create threads 
  printf("create threads\n");
  pthread_t reader, munch1, munch2, writer;
  int readerRet, munch1Ret, munch2Ret, writerRet;
  readerRet = pthread_create(&reader, NULL, &readStart, (void*) readerParams);
  munch1Ret = pthread_create(&munch1, NULL, &munchOneStart, (void*) munchOneParams);
  munch2Ret = pthread_create(&munch2, NULL, &munchTwoStart, (void*) munchTwoParams);
  writerRet = pthread_create(&writer, NULL, &writeStart, (void*) writerParams);

  printf("join threads\n");
  pthread_join(reader, NULL);
  pthread_join(munch1, NULL);
  pthread_join(munch2, NULL);
  pthread_join(writer, NULL);

  printf("exit statuses %d %d %d %d\n", readerRet, munch1Ret, munch2Ret, writerRet);
}

void readStart(void *args) {
  printf("read start\n");
  ThreadParams *params = (ThreadParams *) args;
  feedInput(params->qout, BUFF_SIZE);
}

void munchOneStart(void *args) {
  printf("munch1 start\n");
  ThreadParams *params = (ThreadParams *) args;
  munchOne(params->qin, params->qout);
}

void munchTwoStart(void *args) {
  printf("munch2 start\n");
  ThreadParams *params = (ThreadParams *) args;
  munchTwo(params->qin, params->qout);
}

void writeStart(void *args) {
  printf("write start\n");
  ThreadParams *params = (ThreadParams *) args;
  writeStrings(params->qin);
}

