#include "./interfaces/reader.h"
#include "./interfaces/munch1.h"
#include "./interfaces/munch2.h"
#include "./interfaces/writer.h"
#include "./types/synchronized_queue.h"

const int BUFF_SIZE = 50;
const int QUEUE_SIZE = 10;

int main(int argc, char **argv) {
  Queue *in = CreateStringQueue(QUEUE_SIZE);
  Queue *out = CreateStringQueue(QUEUE_SIZE);

  feedInput(in, BUFF_SIZE);

  // for(int i = 0; i < 8; i++) {
  //   char *s = DequeueString(in);
  //   if (s) {
  //     printf("%s\n", s);
  //   } else {
  //     printf("END\n");
  //   }
  // }

  munchOne(in , out);
  munchTwo(out, in);
  writeStrings(in);
}