CC=g++
CFLAGS=-Wall -c -Wno-write-strings
LDFLAGS=-lwiringPi -lpthread
BINARIES=*.o

all: PiSwitch.o

PiSwitch.o:
	$(CC) $(CFLAGS) PiSwitch.cpp -o PiSwitch.o $(LDFLAGS)
	
test: test.cpp
	$(CC) test.cpp -o test.o $(LDFLAGS)
	
test_receive: test_receive.cpp
	$(CC) test_receive.cpp -o test_receive.o $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(BINARIES)
