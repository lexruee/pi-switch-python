# Pi Switch

Pi Switch is a library for controlling 315/433MHz remote power outlet sockets.

Pi Switch is a port of the [rc-switch](http://code.google.com/p/rc-switch/) library
for the Raspberry Pi and Python Programming Language.



## Installation
First we need to install [wiring pi](http://wiringpi.com/download-and-install/):

```bash
git clone git://git.drogon.net/wiringPi
```

```bash
cd wiringPi
./build
```

In a next step we run pip:
```
sudo pip install pi_switch
```

## Building from source

Install all necessary dependencies:

  - wiringPi
  - python boost
  - python-dev header files

### WiringPi
```bash
  git clone git://git.drogon.net/wiringPi
```

```bash
  cd wiringPi
  ./build
```

### Python-dev / Python boost
```bash
 sudo apt-get install python-dev libboost-python-dev
```

Run the build script:

```bash
 python setup.py build
```
