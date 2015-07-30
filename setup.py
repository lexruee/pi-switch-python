#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup
from distutils.extension import Extension

VERSION = "0.3.1"

setup(
    name="pi_switch",
    packages = [ "pi_switch" ],
    version = VERSION,
    description = "A library for the raspberry pi to control remote power outlet sockets.",
    author = "Alexander Rüedlinger",
    author_email = "a.rueedlinger@gmail.com",
    url = "https://github.com/lexruee/pi-switch-python",
    download_url = "https://github.com/lexruee/pi-switch-python/tarball/%s" % VERSION,
    keywords = ['switch', 'outlet sockets', 'control', 'remote', 'raspberry pi'],
    classifiers = [
        "License :: OSI Approved :: GNU General Public License v2 (GPLv2)",
        "Development Status :: 3 - Alpha",
        "Operating System :: Other OS",
        "Intended Audience :: Developers",
        "Topic :: System :: Hardware",
        "Programming Language :: Python",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Environment :: Other Environment"
    ],
    ext_modules = [
        Extension("_pi_switch",
                    sources = [
                        "pi_switch/wrapper/pi_switch.cpp"
                    ],
                    libraries = ["boost_python", "wiringPi"],
                    extra_compile_args=[
                    '-Wno-write-strings'
                    ])
    ],
    long_description = """\
Pi Switch
-------------------------------------

Pi Switch is a library for controlling 315/433MHz remote power outlet sockets.

This library is a port of the Arduino rc-switch library for the Raspberry Pi and the Python Programming Language.
"""
)
