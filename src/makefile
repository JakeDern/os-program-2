CC = gcc
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o synchronized_queue.o munch1.o munch2.o reader.o writer.o
	$(CC) -o $(EXE) main.o synchronized_queue.o munch1.o munch2.o reader.o writer.o

main.o: main.c 
	$(CC) $(WARNING_FLAGS) -c main.c

synchronized_queue.o:  
	$(CC) $(WARNING_FLAGS) -c ./types/synchronized_queue.c

munch1.o: 
	$(CC) $(WARNING_FLAGS) -c ./modules/munch1.c

munch2.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/munch2.c

reader.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/reader.c

writer.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/writer.c

clean:
	rm $(EXE) *.o

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
