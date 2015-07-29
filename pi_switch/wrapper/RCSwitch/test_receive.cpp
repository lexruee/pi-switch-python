/*
 * Simple receive test program.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "PiSwitch.cpp"


int main(int argc, char* argv[]) {
	int PIN = 0; // PIN 11
	if(wiringPiSetup()!= -1) {
		RCSwitchReceiver receiver;
		receiver.enableReceive(PIN);
		
		while(1) {
			if(receiver.available()) {
				int received_value = receiver.getReceivedValue();
				if(received_value) {
					printf("value: %i\n", received_value);
				} else {
					printf("Unknown encoding\n");
				}
				receiver.resetAvailable();
			}
		}
		
	}
}
