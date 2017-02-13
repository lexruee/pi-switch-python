PYTHON=python2.7 # python3.4
PYTHON_BOOST=-lboost_python #-lboost_python-py34
CCX=g++
CXXFLAGS=-DRPI -Wall -Wno-write-strings -fPIC -I/usr/include/$(PYTHON)
LDFLAGS=-lwiringPi -lpthread $(PYTHON_BOOST)
BINARIES=*.o
LIBS=*.so


all: _pi_switch.so

_pi_switch.so:
	$(CCX) $(CXXFLAGS) rc-switch/RCSwitch.cpp PiSwitch.cpp PiSwitchBoost.cpp -shared -o _pi_switch.so $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(BINARIES) $(LIBS)
