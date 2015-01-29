# Pi Switch

[Pi Switch](https://pypi.python.org/pypi/pi_switch/) is a library for controlling 315/433MHz remote power outlet sockets.

This library is a port of the Arduino [rc-switch](http://code.google.com/p/rc-switch/) library
for the Raspberry Pi and the Python Programming Language.

## Credits
Thanks to Gordon Henderson for [WiringPi](http://wiringpi.com/) and the [rc-switch](http://code.google.com/p/rc-switch/) team for the effort for developing such cool libraries!

## Installation
We need to install the following dependencies:

- wiringPi
- python boost
- python-dev header files
- python-pip

Install [wiring pi](http://wiringpi.com/download-and-install/):

```bash
git clone git://git.drogon.net/wiringPi
```

```bash
cd wiringPi
./build
```

In a next step please update your Raspberry Pi:

```bash
sudo apt-get update
```

Install python boost, python header files and python-pip:

```bash
sudo apt-get install python-dev libboost-python-dev python-pip
```

Finally, we install ```pi_switch``` using pip:

```bash
sudo pip install pi_switch
```

## Usage

Known devices that seem to work are listed on the [rc-switch wiki](http://code.google.com/p/rc-switch/wiki/List_KnownDevices).

Pi Switch uses the wiringPi library and the wiringPi pin [mapping](http://wiringpi.com/pins/).

Example:

```
WiringPi Pin 0 <=> BCM GPIO17 <=> Header Pin 11
```

Programs that use pi_switch must be run with sudo.

### Example program
```python
""" A program that toggles three light switches """
import time
import pi_switch

def create_switch(addr, channel):
  """creates a switch of type B"""
  switch = pi_switch.RCSwitchB(addr, channel)
  switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17
  return switch


def toggle(switch):
  """toggles a switch on and off"""
  switch.switchOn()
  time.sleep(1)
  switch.switchOff()
  time.sleep(1)


switches = [[1,1],[1,2],[1,3]]
switches = [ create_switch(p,q) for (p,q) in switches ]

while True:
  for switch in switches:
    toggle(switch)
```


## Switch Types

There are 4 kind of [switch types](http://code.google.com/p/rc-switch/wiki/HowTo_OperateLowCostOutlets) according the rc-switch wiki.

 * Type A - 10 pole DIP switches
 * Type B - Two rotary/sliding switches
 * Type C -  Intertechno
 * Type D

### Switch Type A

NOTE: NOT tested!

```python
import pi_switch

# DIP switches 1..5 where "1" = on and "0" = off,
# if all DIP switches are on it's "11111"
first = "11111"

# DIP switches 6..10 (A..E) where "1" = on and "0" = off,
# if all DIP switches are on it's "11111"
second = "11111"

switch = pi_switch.RCSwitchA(first, second)
switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```

### Switch Type B
NOTE: Tested and works!

```python
import pi_switch

address_group = 1 # Address group (1..4)
channel = 2 # Channel (1..4)

switch = rc_switch.RCSwitchB(address_group, channel)
switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```

### Switch Type C
NOTE: Not tested!

```python
import pi_switch

family_code = "a" # Familycode (a..f)
group = 1 # Number of group (1..4)
device = 1 # Number of device (1..4)

switch = pi_switch.RCSwitchC(family_code, group, device) #address group 1, channel 2
switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```

### Switch Type D
NOTE: Not tested!

```python
import pi_switch

group = "A" # Code of the switch group (A,B,C,D)
device = 1 # Number of the switch itself (1..3)

switch = pi_switch.RCSwitchD(group, device) #address group 1, channel 2
switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```

## Disclaimer
I'm not responsible for any hardware damages or other accidents.

You use this library at your own risk.
