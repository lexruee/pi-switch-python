PYTHON=python2.7
PYTHON_BOOST=-lboost_python
CCX=g++
CXXFLAGS=-DRPI -Wall -c -Wno-write-strings -I/usr/include/$(PYTHON)
LDFLAGS=-lwiringPi -lpthread $(PYTHON_BOOST)
BINARIES=RCSwitch.o PiSwitch.o PiSwitchBoost.o


all: $(BINARIES)

RCSwitch.o:
	$(CCX) $(CXXFLAGS) rc-switch/RCSwitch.cpp -o RCSwitch.o $(LDFLAGS)

PiSwitch.o: RCSwitch.o
	$(CCX) $(CXXFLAGS) PiSwitch.cpp -o PiSwitch.o $(LDFLAGS)

PiSwitchBoost.o: PiSwitch.o RCSwitch.o
	$(CCX) $(CXXFLAGS) PiSwitchBoost.cpp -o PiSwitchBoost.o $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(BINARIES)
