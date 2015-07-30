# -*- coding: utf-8 -*-
"""
@author     Alexander Rüedlinger <a.rueedlinger@gmail.com>
@date       30.07.2015

"""

import time
from pi_switch import RCSwitchB

switch = RCSwitchB(1, 3)
switch.enableTransmit(0)

time.sleep(0.2)
switch.switchOn()

time.sleep(2)
switch.switchOff()














