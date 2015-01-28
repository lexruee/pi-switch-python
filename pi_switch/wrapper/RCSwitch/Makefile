CC=g++
CFLAGS=-Wall -c
LDFLAGS=-lwiringPi -lpthread 

all: PiSwitch.o

PiSwitch.o:
	$(CC) $(CFLAGS) PiSwitch.cpp -o PiSwitch.o $(LDFLAGS)
	
test: test.cpp
	$(CC) test.cpp -o test.o $(LDFLAGS)

clean:
	rm *.o
