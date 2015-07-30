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

#ifndef __PI_SWITCH__
#define __PI_SWITCH__

// return error code
#define WIRINGPI_CODES		1

// necessary values to port rc-switch to the raspberry pi
#ifndef boolean
#define boolean int
#endif

#ifndef byte
#define byte char
#endif

#ifndef CHANGE
#define CHANGE INT_EDGE_BOTH
#endif

// replace detachInterrupt() with a empty block
#define detachInterrupt(x) do { } while(0)

// map attachInterrupt() to wiringPi equivalent
#define attachInterrupt(pin, handler, edgeType)		\
		do {	 									\
			wiringPiISR(pin, edgeType, &handler);	\
		} while(0)									\


#include "RCSwitch.h"
#include <string>
#include <cstring>

/*
 * Abstract RCSwitchProxy class for providing a easier way to use
 * the RCSwitch library.
 */
class RCSwitchProxy {
	public:
		virtual void switchOn() = 0;
		virtual void switchOff() = 0;
		void enableTransmit(int);
		void disableTransmit();

	protected:
		RCSwitch *rcSwitch;
		void init();
		void destroy();
};

class RCSwitchSender {
	public:
		RCSwitchSender();
		~RCSwitchSender();
		void sendTriState(std::string Code);
		void send(unsigned long Code, unsigned int length);
		void send(std::string Code);
		void enableTransmit(int nTransmitterPin);
		void disableTransmit();
		void setPulseLength(int nPulseLength);
		void setRepeatTransmit(int nRepeatTransmit);
		void setProtocol(int nProtocol);
		void setProtocol(int nProtocol, int nPulseLength);

	protected:
		RCSwitch *rcSwitch;
};

class RCSwitchReceiver {
	public:
		RCSwitchReceiver();
		~RCSwitchReceiver();
		void enableReceive(int pin);
		bool available();
		void resetAvailable();
		unsigned long getReceivedValue();
		unsigned int getReceivedBitlength();
		unsigned int getReceivedDelay();
		unsigned int getReceivedProtocol();
		unsigned int* getReceivedRawdata();
		
	protected:
		RCSwitch *rcSwitch;
};
#endif
