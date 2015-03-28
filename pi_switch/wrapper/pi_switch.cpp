/*
PiSwitch - RaspberryPi library for remote control outlet switches
Copyright (c) 2015 Alexander Rueedlinger.  All right reserved.

Project home: https://github.com/lexruee/pi-switch-python

This library is a port of the RCSwitch - Arduino library.
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

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>



// use boost namespace to avoid lot of typing :-)
using namespace boost::python;

#include "RCSwitch/PiSwitch.cpp"

// Helper struct to wrap the proxy class. It does the job!
// Note: RCSwitchProxyWrap MUST BE a struct otherwise it won't work!
struct RCSwitchProxyWrap: RCSwitchProxy, wrapper<RCSwitchProxy> {
  void switchOn() {
    this->get_override("switchOn")();
  }

  void switchOff() {
    this->get_override("switchOff")();
  }
};


BOOST_PYTHON_MODULE(pi_switch_wrapper) {
  wiringPiSetup();

  // map RCSwitchSender class
  void (RCSwitchSender::*send)(std::string) = &RCSwitchSender::send;
  void (RCSwitchSender::*sendDecimal)(unsigned long Code, unsigned int length) = &RCSwitchSender::send;
  void (RCSwitchSender::*setProtocol)(int) = &RCSwitchSender::setProtocol;
  
  class_<RCSwitchSender>("RCSwitchSender")
    .def("sendTriState", &RCSwitchSender::sendTriState)
    .def("sendDecimal", sendDecimal)
    .def("send", send)
    .def("enableTransmit", &RCSwitchSender::enableTransmit)
    .def("disableTransmit", &RCSwitchSender::disableTransmit)
    .def("setPulseLength", &RCSwitchSender::setPulseLength)
    .def("setRepeatTransmit", &RCSwitchSender::setRepeatTransmit)
    .def("setProtocol", setProtocol);

  // map RCSwitchProxy class
  class_<RCSwitchProxyWrap,boost::noncopyable>("RCSwitchProxy")
    .def("switchOn", pure_virtual(&RCSwitchProxy::switchOn))
    .def("switchOff", pure_virtual(&RCSwitchProxy::switchOff))
    .def("enableTransmit", &RCSwitchProxy::enableTransmit)
    .def("disableTransmit", &RCSwitchProxy::disableTransmit);

  // map switch types
  class_<RCSwitchA, bases<RCSwitchProxy> >("RCSwitchA", init<std::string, std::string>());
  class_<RCSwitchB, bases<RCSwitchProxy> >("RCSwitchB", init<int, int>());
  class_<RCSwitchC, bases<RCSwitchProxy> >("RCSwitchC", init<std::string, int, int>());
  class_<RCSwitchD, bases<RCSwitchProxy> >("RCSwitchD", init<std::string, int>());
}
