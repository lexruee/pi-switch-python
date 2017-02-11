#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup
from distutils.extension import Extension
from distutils.command.build_ext import build_ext
from distutils.sysconfig import customize_compiler

VERSION = "0.5.0.dev"


class CustomBuildExt(build_ext):
    """
    Fixes: cc1plus: warning: command line option “-Wstrict-prototypes”
    More details at:
    http://stackoverflow.com/questions/8106258/cc1plus-warning-command-line-option-wstrict-prototypes-is-valid-for-ada-c-o
    """

    def build_extensions(self):
        customize_compiler(self.compiler)
        try:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        except (AttributeError, ValueError):
            pass
        build_ext.build_extensions(self)

setup(
    name="pi_switch",
    packages = [ "pi_switch" ],
    version = VERSION,
    description = "A Python library for the Raspberry Pi to control remote power sockets using rc-switch.",
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
    cmdclass = {'build_ext': CustomBuildExt},
    ext_modules = [
        Extension("_pi_switch",
                    sources = [
                        "pi_switch/wrapper/rc-switch/RCSwitch.cpp",
                        "pi_switch/wrapper/PiSwitch.cpp",
                        "pi_switch/wrapper/PiSwitchBoost.cpp"
                    ],
                    libraries = ["boost_python", "wiringPi"],
                    extra_compile_args=[
                    '-DRPI', '-Wall', '-Wno-write-strings'
                    ])
    ],
    long_description = """\
Pi Switch
-------------------------------------

Pi Switch is a library for controlling 315/433MHz remote power sockets.

This library is a wrapper of the Arduino rc-switch library for the Raspberry Pi and the Python Programming Language.
"""
)
