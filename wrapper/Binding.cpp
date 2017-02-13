/*
PiSwitch - A Python wrapper around the rc-switch library for the Raspberry Pi
Copyright (c) 2015-2017 Alexander Rueedlinger.  All right reserved.

	Project home: https://github.com/lexruee/pi-switch-python

The source code of rc-switch library can be found at:
	Project home: https://github.com/sui77/rc-switch

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

#include "./pybind11/include/pybind11/pybind11.h"
#include "./rc-switch/RCSwitch.h"
#include "./PiSwitch.h"

namespace py = pybind11;

// helper class to map RCSwitchProxy
class PyRCSwitchProxy : RCSwitchProxy {
    public:
        using RCSwitchProxy::RCSwitchProxy;
        void switchOn() override {
            PYBIND11_OVERLOAD_PURE(void, RCSwitchProxy, switchOn);
        }
		void switchOff() override {
            PYBIND11_OVERLOAD_PURE(void, RCSwitchProxy, switchOff);
        }
};


PYBIND11_PLUGIN(_pi_switch) {

    py::module m("_pi_switch", "Python wrapper around rc-switch.");

    m.def("wiringPiSetup", &wiringPiSetup, "Use the wiringPi pin numbering scheme.");
    m.def("wiringPiSetupGpio", &wiringPiSetupGpio, "Use the Broadcom GPIO numbering scheme.");
    m.def("wiringPiSetupPhys", &wiringPiSetupPhys, "Use the physical pin numbering scheme.");

    // bind RCSwitchSender class
    py::class_<RCSwitchSender>(m, "RCSwitchSender")
        .def(py::init<>())
        .def("sendTriState", &RCSwitchSender::sendTriState)
        .def("sendDecimal", (void (RCSwitchSender::*)(unsigned long, unsigned int)) &RCSwitchSender::send)
        .def("send", (void (RCSwitchSender::*)(std::string)) &RCSwitchSender::send)
        .def("enableTransmit", &RCSwitchSender::enableTransmit)
        .def("disableTransmit", &RCSwitchSender::disableTransmit)
        .def("setPulseLength", &RCSwitchSender::setPulseLength)
        .def("setRepeatTransmit", &RCSwitchSender::setRepeatTransmit)
        .def("setProtocol", (void (RCSwitchSender::*)(int)) &RCSwitchSender::setProtocol);

    // bind RCSwitchReceiver class
    py::class_<RCSwitchReceiver>(m, "RCSwitchReceiver")
        .def(py::init<>())
	    .def("enableReceive", &RCSwitchReceiver::enableReceive)
	    .def("available", &RCSwitchReceiver::available)
	    .def("resetAvailable", &RCSwitchReceiver::resetAvailable)
	    .def("getReceivedValue", &RCSwitchReceiver::getReceivedValue)
	    .def("getReceivedBitlength", &RCSwitchReceiver::getReceivedBitlength)
	    .def("getReceivedDelay", &RCSwitchReceiver::getReceivedDelay)
	    .def("getReceivedProtocol", &RCSwitchReceiver::getReceivedProtocol);

    // bind RCSwitchProxy class
    py::class_<RCSwitchProxy, PyRCSwitchProxy> proxy(m, "RCSwitchProxy");
    proxy
        .def(py::init<>())
        .def("switchOn", &RCSwitchProxy::switchOn)
        .def("switchOff", &RCSwitchProxy::switchOff)
        .def("enableTransmit", &RCSwitchProxy::enableTransmit)
        .def("disableTransmit", &RCSwitchProxy::disableTransmit);

    // bind switch classes
    py::class_<RCSwitchA, RCSwitchProxy> (m, "RCSwitchA")
        .def(py::init<std::string, std::string>());

    py::class_<RCSwitchB, RCSwitchProxy> (m, "RCSwitchB")
        .def(py::init<int, int>());

    py::class_<RCSwitchC, RCSwitchProxy> (m, "RCSwitchC")
        .def(py::init<std::string, int, int>());

    py::class_<RCSwitchD, RCSwitchProxy> (m, "RCSwitchD")
        .def(py::init<std::string, int>());

    return m.ptr();
}