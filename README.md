# Pi Switch

Pi Switch is a library for controlling 315/433MHz remote power outlet sockets.

This library is a port of the [rc-switch](http://code.google.com/p/rc-switch/) library
for the Raspberry Pi and Python Programming Language.

## Installation
We need to install the following dependencies:

- wiringPi
- python boost
- python-dev header files

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

Install python boost and the python header files:

```bash
sudo apt-get install python-dev libboost-python-dev
```

Finally, we install ```pi_switch``` using pip:

```bash
sudo pip install pi_switch
```

## Usage

Known devices that seem to work are listed on the [rc-switch wiki](http://code.google.com/p/rc-switch/wiki/List_KnownDevices).

This library uses the wiring pi pin [mapping](http://wiringpi.com/pins/).

Example: WiringPi Pin 0 <=> BCM GPIO17 <=> Header Pin 11

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
switch.enableTransmit(0) # use gpio pin 0 <=> GPIO17

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
switch.enableTransmit(0) # use gpio pin 0 <=> GPIO17

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
switch.enableTransmit(0) # use gpio pin 0 <=> GPIO17

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
switch.enableTransmit(0) # use gpio pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```
