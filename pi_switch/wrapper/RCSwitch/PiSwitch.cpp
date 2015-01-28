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

#include "PiSwitch.h"
#include "RCSwitch.cpp"

/*
 * This file provides Proxy classes for all available RCSwitch types:
 *	- Type A with 10 pole DIP switches
 *	- Type B with two rotary/sliding switches
 *  - Type C Intertechno
 *  - Type D REV
 *
 * Besides that a RCSwitchSender class is provided to
 * create new switch types in a more OOP way.
 */


/*
 * RCSwitchSender implementation.
 */

RCSwitchSender::RCSwitchSender() {
	this->rcSwitch = new RCSwitch;
}

RCSwitchSender::~RCSwitchSender() {
	delete rcSwitch;
}

void RCSwitchSender::sendTriState(std::string Code) {
	char *cCode = new char[Code.length()+1];
	std::strcpy(cCode, Code.c_str());
	rcSwitch->sendTriState(cCode);
	delete[] cCode;
}

void RCSwitchSender::send(unsigned long Code, unsigned int length) {
	rcSwitch->send(Code, length);
}

void RCSwitchSender::send(std::string Code) {
	char *cCode = new char[Code.length()+1];
	std::strcpy(cCode, Code.c_str());
	rcSwitch->send(cCode);
	delete[] cCode;
}

void RCSwitchSender::enableTransmit(int nTransmitterPin) {
	rcSwitch->enableTransmit(nTransmitterPin);
}

void RCSwitchSender::disableTransmit() {
	rcSwitch->disableTransmit();
}

void RCSwitchSender::setPulseLength(int nPulseLength) {
	rcSwitch->setPulseLength(nPulseLength);
}

void RCSwitchSender::setRepeatTransmit(int nRepeatTransmit) {
	rcSwitch->setRepeatTransmit(nRepeatTransmit);
}

void RCSwitchSender::setProtocol(int nProtocol) {
	rcSwitch->setProtocol(nProtocol);
}

void RCSwitchSender::setProtocol(int nProtocol, int nPulseLength) {
	rcSwitch->setProtocol(nProtocol, nPulseLength);
}


/*
 * RCSwitchProxy implementation.
 */
void RCSwitchProxy::init() {
	 this->rcSwitch = new RCSwitch;
}

void RCSwitchProxy::enableTransmit(int pin) {
	rcSwitch->enableTransmit(pin);
}


void RCSwitchProxy::disableTransmit() {
	rcSwitch->disableTransmit();
}

void RCSwitchProxy::destroy(){
	 delete rcSwitch;
}


/*
 * RCSwitch type A implementation.
 */
class RCSwitchA: public RCSwitchProxy {
	public:
		RCSwitchA(std::string groupCode, std::string deviceCode){
			cDeviceCode = new char[deviceCode.length()+1];
			cGroupCode = new char[groupCode.length()+1];
			std::strcpy(cDeviceCode, deviceCode.c_str());
			std::strcpy(cGroupCode, groupCode.c_str());
			this->init();
		}

		void switchOn(){
			rcSwitch->switchOn(cGroupCode, cDeviceCode);
		}

		void switchOff(){
			rcSwitch->switchOff(cGroupCode, cDeviceCode);
		}

		~RCSwitchA(){
			this->destroy();
			delete[] cGroupCode;
			delete[] cDeviceCode;
		}

	private:
		char *cGroupCode;
		char *cDeviceCode;
};


/*
 * RCSwitch type B implementation.
 */
class RCSwitchB: public RCSwitchProxy {
	public:
		RCSwitchB(int addressCode, int channelCode) {
			this->addressCode = addressCode;
			this->channelCode = channelCode;
			this->init();
		}

		void switchOn(){
			rcSwitch->switchOn(addressCode, channelCode);
		}

		void switchOff(){
			rcSwitch->switchOff(addressCode, channelCode);
		}

		~RCSwitchB(){
			this->destroy();
		}

	private:
		int addressCode;
		int channelCode;
};


/*
 * RCSwitch type C implementation.
 */
class RCSwitchC: public RCSwitchProxy {
	public:
		RCSwitchC(std::string family, int groupCode, int deviceCode) {
			this->family = family;
			this->deviceCode = deviceCode;
			this->groupCode = groupCode;
			this->init();
		}

		void switchOn(){
			rcSwitch->switchOn(family[0], groupCode, deviceCode);
		}

		void switchOff(){
			rcSwitch->switchOff(family[0], groupCode, deviceCode);
		}

		~RCSwitchC(){
			this->destroy();
		}

	private:
		std::string family;
		int groupCode;
		int deviceCode;
};


/*
 * RCSwitch type D implementation.
 */
class RCSwitchD: public RCSwitchProxy {
	public:
		RCSwitchD(std::string groupCode, int deviceCode) {
			this->groupCode = groupCode;
			this->deviceCode = deviceCode;
			this->init();
		}

		void switchOn(){
			rcSwitch->switchOn(groupCode[0], deviceCode);
		}

		void switchOff(){
			rcSwitch->switchOff(groupCode[0], deviceCode);
		}

		~RCSwitchD(){
			this->destroy();
		}

	private:
		std::string groupCode;
		int deviceCode;
};
