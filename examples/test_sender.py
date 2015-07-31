# -*- coding: utf-8 -*-
"""
@author     Alexander Rüedlinger <a.rueedlinger@gmail.com>
@date       30.07.2015

"""
import time
from pi_switch import RCSwitchSender

sender = RCSwitchSender()
sender.enableTransmit(0) # use WiringPi pin 0

num = 1
while True:
        time.sleep(2)
        sender.sendDecimal(num, 24)
        num += 1
