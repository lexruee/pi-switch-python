/*
PiSwitch - RaspberryPi library for remote control outlet switches
Copyright (c) 2015 Alexander Rueedlinger.  All right reserved.

	Project home: https://github.com/lexruee/pi_switch

This library is a port of the RCSwitch - Arduino library.
	Project home: http://code.google.com/p/rc-switch/

	The RCSwitch team did a great job for providing us such a great
	library! So thanks to all RCSwitch contributors:
		- Suat Özgür
		- Andre Koehler
		- Gordeev Andrey Vladimirovich
		- Skineffect
		- Dominik Fischer
		- Frank Oltmanns
		- Andreas Steinel

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include "PiSwitch.cpp"

int main(int argc, char* argv[]) {
	if(argc == 4){
		wiringPiSetup();
		int PIN = 0; // PIN 11
		int addressCode = atoi(argv[1]);
		int channelCode = atoi(argv[2]);
		int state = atoi(argv[3]);

		printf("addressCode: %i \t channelState: %i, switch: %s\n", addressCode, channelCode, (state % 2 == 0 ) ? "off" : "on");

		RCSwitchProxy *piSwitch = new RCSwitchB(addressCode, channelCode);
		piSwitch->enableTransmit(PIN);

		if(state)
			piSwitch->switchOn();
		else
			piSwitch->switchOff();

		delete piSwitch;
	} else {
		printf("Need three parameters: addressCode, channelCode, state\n");
	}

	return 0;
}
