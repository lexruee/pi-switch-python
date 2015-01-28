#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension

setup(
    name="pi_switch",
    packages = [ "pi_switch" ],
    version = "0.1.1",
    description = "A library for the raspberry pi to control remote power outlet sockets.",
    author = "Alexander Rueedlinger",
    author_email = "a.rueedlinger@gmail.com",
    url = "https://github.com/lexruee/pi-switch-python",
    #download_url = "https://github.com/lexruee/pi-switch-python/tarball/0.1",
    keywords = ['switch', 'outlet sockets', 'control', 'remote', 'raspberry pi'],
    classifiers = [
        "License :: OSI Approved :: GNU General Public License v2 (GPLv2)"
    ],
    ext_modules = [
        Extension("pi_switch_wrapper",
                    sources = [
                        "pi_switch/wrapper/pi_switch.cpp"
                    ],
                    libraries = ["boost_python", "wiringPi"])
    ])
