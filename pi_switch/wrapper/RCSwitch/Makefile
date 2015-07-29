CC=g++
CFLAGS=-Wall -c
LDFLAGS=-lwiringPi -lpthread 

all: PiSwitch.o

PiSwitch.o:
	$(CC) $(CFLAGS) PiSwitch.cpp -o PiSwitch.o $(LDFLAGS)
	
test: test.cpp
	$(CC) test.cpp -o test.o $(LDFLAGS)
	
test: test_receive.cpp
	$(CC) test_receive.cpp -o test_receive.o $(LDFLAGS)

clean:
	rm *.o
