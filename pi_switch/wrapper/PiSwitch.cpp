/*
PiSwitch - A Python wrapper around the rc-switch library for the Raspberry Pi
Copyright (c) 2015-2017 Alexander Rueedlinger.  All right reserved.

	Project home: https://github.com/lexruee/pi_switch

The source code of rc-switch library can be found at:
	Project home: http://code.google.com/p/rc-switch/

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

#include "./PiSwitch.h"
#include "./rc-switch/RCSwitch.h"

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
 * RCSwitchReceiver implementation.
 */
 
RCSwitchReceiver::RCSwitchReceiver() {
	this->rcSwitch = new RCSwitch;
}


RCSwitchReceiver::~RCSwitchReceiver() {
	delete rcSwitch;
}

void RCSwitchReceiver::enableReceive(int pin) {
	rcSwitch->enableReceive(pin);
}

bool RCSwitchReceiver::available() {
	return rcSwitch->available();
}

void RCSwitchReceiver::resetAvailable() {
	rcSwitch->resetAvailable();
}

unsigned long RCSwitchReceiver::getReceivedValue() {
	return rcSwitch->getReceivedValue();
}

unsigned int RCSwitchReceiver::getReceivedDelay() {
	return rcSwitch->getReceivedDelay();
}

unsigned int RCSwitchReceiver::getReceivedProtocol() {
	return rcSwitch->getReceivedProtocol();
}

unsigned int* RCSwitchReceiver::getReceivedRawdata() {
	return rcSwitch->getReceivedRawdata();
}

unsigned int RCSwitchReceiver::getReceivedBitlength() {
	return rcSwitch->getReceivedBitlength();
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

void RCSwitchProxy::destroy() {
	 delete rcSwitch;
}


/*
 * RCSwitch type A implementation.
 */
RCSwitchA::RCSwitchA(std::string groupCode, std::string deviceCode){
    cDeviceCode = new char[deviceCode.length()+1];
    cGroupCode = new char[groupCode.length()+1];
	std::strcpy(cDeviceCode, deviceCode.c_str());
	std::strcpy(cGroupCode, groupCode.c_str());
	this->init();
}

void RCSwitchA::switchOn() {
	rcSwitch->switchOn(cGroupCode, cDeviceCode);
}

void RCSwitchA::switchOff() {
	rcSwitch->switchOff(cGroupCode, cDeviceCode);
}

RCSwitchA::~RCSwitchA() {
	this->destroy();
	delete[] cGroupCode;
	delete[] cDeviceCode;
}


/*
 * RCSwitch type B implementation.
 */
RCSwitchB::RCSwitchB(int addressCode, int channelCode) {
	this->addressCode = addressCode;
	this->channelCode = channelCode;
	this->init();
}

void RCSwitchB::switchOn() {
	rcSwitch->switchOn(addressCode, channelCode);
}

void RCSwitchB::switchOff() {
	rcSwitch->switchOff(addressCode, channelCode);
}

RCSwitchB::~RCSwitchB() {
	this->destroy();
}


/*
 * RCSwitch type C implementation.
 */
RCSwitchC::RCSwitchC(std::string family, int groupCode, int deviceCode) {
	this->family = family;
	this->deviceCode = deviceCode;
	this->groupCode = groupCode;
	this->init();
}

void RCSwitchC::switchOn() {
	rcSwitch->switchOn(family[0], groupCode, deviceCode);
}

void RCSwitchC::switchOff() {
	rcSwitch->switchOff(family[0], groupCode, deviceCode);
}

RCSwitchC::~RCSwitchC() {
	this->destroy();
}


/*
 * RCSwitch type D implementation.
 */
RCSwitchD::RCSwitchD(std::string groupCode, int deviceCode) {
	this->groupCode = groupCode;
	this->deviceCode = deviceCode;
	this->init();
}

void RCSwitchD::switchOn() {
	rcSwitch->switchOn(groupCode[0], deviceCode);
}

void RCSwitchD::switchOff() {
	rcSwitch->switchOff(groupCode[0], deviceCode);
}

RCSwitchD::~RCSwitchD() {
	this->destroy();
}

