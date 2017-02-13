import _pi_switch
from _pi_switch import RCSwitchA, RCSwitchB, RCSwitchC, RCSwitchD, RCSwitchSender, RCSwitchReceiver, RCSwitchProxy

_pi_switch.wiringPiSetup()

__all__ = ('RCSwitchA', 'RCSwitchB', 'RCSwitchC', 'RCSwitchD', 'RCSwitchSender', 'RCSwitchReceiver', 'RCSwitchProxy')

