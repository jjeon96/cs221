CC=g++
CFLAGS=-Wall -O3
PROG=runway
TEST=LQueue_driver
OBJS1=runway.o LQueue.o
OBJS2=LQueue_driver.o LQueue.o

all: runway LQueue_driver

runway: $(OBJS1)
	$(CC) -o $(PROG) $(OBJS1)

LQueue_driver: $(OBJS2)
	$(CC) -o $(TEST) $(OBJS2)

.C.o:
	$(CC) $(CFLAGS) -c $*.C

LQueue.o:	LQueue.h

LQueue_driver.o:	LQueue_driver.C LQueue.o LQueue.h

runway.o: runway.C LQueue.o LQueue.h

clean:
	rm *.o LQueue_driver runway
