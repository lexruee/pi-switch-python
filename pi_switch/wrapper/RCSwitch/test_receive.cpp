/*
 * @date    30.07.2015
 * @author  Alexander Rüedlinger <a.rueedlinger@gmail.com>
 * 
 * Simple receive test program.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "PiSwitch.cpp"


int main(int argc, char* argv[]) {
	int PIN = 2; // PIN 13
	
	if(wiringPiSetup()!= -1) {
		RCSwitchReceiver receiver;
		receiver.enableReceive(PIN);
		
		while(1) {
			if(receiver.available()) {
				int received_value = receiver.getReceivedValue();
				if(received_value) {
					printf("Received ");
					printf("%i", received_value);
					printf(" / ");
					printf("%i", receiver.getReceivedBitlength());
					printf(" bit ");
					printf("Protocol: ");
					printf("%i", receiver.getReceivedProtocol());
					printf("\n");
				} else {
					printf("Unknown encoding\n");
				}
				receiver.resetAvailable();
			}
		}
		
	}
}
