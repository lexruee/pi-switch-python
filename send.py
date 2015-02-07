"""
A program to send off / on commands to a remote power socket.

author:     Alexander Rueedlinger <a.rueedlinger@gmail.com>
date:       02.07.2015

Example:

    switch type A:
    sudo python send.py -c off -t A -s 11111,11111 -p 0

    switch type B:
    sudo python send.py -c off -t B -s 1,3 -p 0

    switch type C:
    sudo python send.py -c off -t C -s a,1,1 -p 0

    switch type D:
    sudo python send.py -c off -t D -s A,1 -p 0

"""

import argparse
import sys

try:
    import pi_switch
except ImportError:
    print "pi_switch import error!"
    sys.exit()

def create_switch(type, settings, pin):
	"""Create a switch.

    Args:
        type: (str): type of the switch [A,B,C,D]
        settings (str): a comma separted list
        pin (int): wiringPi pin

    Returns:
        switch
    """

	switch = None
	if type == "A":
		group, device = settings.split(",")
		switch = pi_switch.RCSwitchA(group, device)

	elif type == "B":
		addr, channel = settings.split(",")
		addr = int(addr)
		channel = int(channel)
		switch = pi_switch.RCSwitchB(addr, channel)

	elif type == "C":
		family, group, device = settings.split(",")
		group = int(group)
		device = int(device)
		switch = pi_switch.RCSwitchC(family, group, device)

	elif type == "D":
		group, device = settings.split(",")
		device = int(device)
		switch = pi_switch.RCSwitchD(group, device)

	else:
		print "Type %s is not supported!" % type
		sys.exit()

	switch.enableTransmit(pin)
	return switch


def toggle(switch, command):
	"""Toggles a switch on or off.

    Args:
        switch (switch): a switch
        command (str): "on" or "off"
    """

	if command in ["on"]:
		switch.switchOn()

	if command in ["off"]:
		switch.switchOff()

def main():
	parser = argparse.ArgumentParser(description="Send off / on commands to a remote power socket.")
	parser.add_argument("-c", dest = "command", metavar = "command", nargs = "?",
		help="can be on or off")

	parser.add_argument("-t", dest = "type", metavar = "type", nargs = "?",
		help="type of the switch: A, B, C or D")

	parser.add_argument("-s", dest = "settings", metavar = "settings", nargs = "?",
		help="settings as a comma separated list: value1,value2,value2")

	parser.add_argument("-p", dest = "pin",  metavar = "pin", type = int, nargs = "?",
		help="wriningPi pin")

	args = parser.parse_args()


	switch = create_switch(args.type, args.settings, args.pin)
	toggle(switch, args.command)

if __name__ == "__main__":
	main()
