# Pi Switch

[![PyPI](https://img.shields.io/pypi/v/pi_switch.svg)]()

[Pi Switch](https://pypi.python.org/pypi/pi_switch/) is a library for controlling 315/433MHz remote power outlet sockets.

This library is a port of the Arduino [rc-switch](http://code.google.com/p/rc-switch/) library
for the Raspberry Pi and the Python Programming Language.

## Credits
Thanks to Gordon Henderson for [WiringPi](http://wiringpi.com/) and the [rc-switch](http://code.google.com/p/rc-switch/) team for the effort for developing such cool libraries!

## Please contribute!
Please contribute to this repository. Every contribution counts.

You can contribute to this project by
 * improving the documentation
  * circuits figures
  * arduino / raspberry pi tutorial etc.
 * starting a github wiki
 * sending pull requests
 * reporting bugs
 * submitting feature requests



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

## Building from source
Please check that all dependencies are installed. See section `Installation`.

```bash
git clone https://github.com/lexruee/pi-switch-python.git
```

```bash
cd pi-switch-python
```

### Testing
If you just want to test it run the build command:

```bash
sudo python setup.py build
```

Change the directory:
```bash
cd build/lib.linux-armv6l-2.7
```

Run python and import ```pi_switch```:
```bash
sudo python
```

### Installation
Install it:

```bash
sudo python setup.py install
```




## Usage

Known devices that seem to work are listed on the [rc-switch wiki](http://code.google.com/p/rc-switch/wiki/List_KnownDevices).

Pi Switch uses the wiringPi library and the wiringPi pin [mapping](http://wiringpi.com/pins/).

Example:

```
WiringPi Pin 0 <=> BCM GPIO17 <=> Header Pin 11
```

Programs that use pi_switch must be run with sudo.

### send.py
[send.py](https://github.com/lexruee/pi-switch-python/blob/master/send.py) is a python program to switch power sockets on or off.

It takes the following arguments:

 * command: -c
 * type: -t
 * settings: -s

The command argument must be either on or off. Type must be A, B, C or D. Settings must be
a comma separated list which specifies the family code, group code, address code, channel number or device number.

For more details about the switch types see the [rc-switch](http://code.google.com/p/rc-switch/wiki/HowTo_OperateLowCostOutlets) wiki page.

```bash
#switch type A:
sudo python send.py -c off -t A -s 11001,01000 -p 0

#switch type B:
sudo python send.py -c off -t B -s 1,3 -p 0

#switch type C:
sudo python send.py -c off -t C -s a,1,1 -p 0

#switch type D:
sudo python send.py -c off -t D -s A,1 -p 0

```


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

## RCSwitchSender

The `RCSwitchSender` class provides low level methods to send binary
or tri-state strings.

For more details see the [rc-switch](https://code.google.com/p/rc-switch/wiki/HowTo_Send) wiki.

### Send binary string

```python
# Type B example: address group = 1, channel = 1
import pi_switch
sender = pi_switch.RCSwitchSender()
sender.enableTransmit(0) # use WiringPi pin 0
sender.send("000101010001010101010101") # switch on
sender.send("000101010001010101010100") # switch off
```

### Send tri-state string

```python
# Type B example: address group = 1, channel = 1
import pi_switch
sender = pi_switch.RCSwitchSender()
sender.enableTransmit(0) # use WiringPi pin 0
sender.sendTriState("0FFF0FFFFFF1") # switch on
sender.sendTriState("0FFF0FFFFFF0") # switch off
```


### Send decimal

```python
# Type B example: address group = 1, channel = 1
import pi_switch
sender = pi_switch.RCSwitchSender()
sender.enableTransmit(0) # use WiringPi pin 0
sender.sendDecimal(1381717, 24) # switch on
sender.sendDecimal(1381716, 24) # switch off
```


### RCSwitchSender setter methods
The default settings of the `RCSwitchSender` can be changed by means of the following setter methods:

  * setProtocol(num)
  * setPulseLength(num)
  * setRepeatTransmit(num)  


## Switch Types

There are 4 kind of [switch types](http://code.google.com/p/rc-switch/wiki/HowTo_OperateLowCostOutlets) according to the rc-switch wiki page.

 * Type A - 10 pole DIP switches
 * Type B - Two rotary/sliding switches
 * Type C -  Intertechno
 * Type D

### Switch Type A

NOTE: Tested and works!

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

switch = pi_switch.RCSwitchB(address_group, channel)
switch.enableTransmit(0) # use WiringPi pin 0 <=> GPIO17

switch.switchOn()
switch.switchOff()
```

### Switch Type C
NOTE: Tested and works! Please make sure to send a 'on' sequence within the first five seconds the switch is plugged. This enables the switch to recognize the family code.

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

## Contributing
Please feel free to contribute or to improve this library (Codebase, Documentation etc.).
I'm not an expert in this field. I'm just the guy who wrote the glue to port the library for the Python Programming Language :-).


1. Fork it ( https://github.com/[my-github-username]/pi-switch-python/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contact

Feel free to send me an email:

```
a.rueedlinger <at> gmail.com
```

## Disclaimer
I'm not responsible for any hardware damages or other accidents.

You use this library at your own risk.
