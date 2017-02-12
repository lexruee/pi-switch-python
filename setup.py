#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext
from distutils.sysconfig import customize_compiler


VERSION = "0.5.0.dev"


if sys.version_info >= (3,):
    BOOST_LIB = 'boost_python-py34'
else:
    BOOST_LIB = 'boost_python'


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
    version = VERSION,
    packages = find_packages(exclude=["*.tests", "*.tests.*", "tests.*", "tests"]),
    scripts = [],
    install_requires=[],
    package_data={},

    cmdclass = {'build_ext': CustomBuildExt},
    ext_modules = [
        Extension("_pi_switch",
                  sources = [
                      "pi_switch/wrapper/rc-switch/RCSwitch.cpp",
                      "pi_switch/wrapper/PiSwitch.cpp",
                      "pi_switch/wrapper/PiSwitchBoost.cpp"
                  ],
                  libraries = [BOOST_LIB, "wiringPi"],
                  extra_compile_args=[
                      '-DRPI', '-Wall', '-Wno-write-strings'
                  ])
    ],

    entry_points={},

    test_suite='nose2.collector.collector',

    description = "Pi Switch is a Python wrapper around the rc-switch library for the Raspberry Pi.",
    author = "Alexander Rüedlinger",
    author_email = "a.rueedlinger@gmail.com",
    url = "https://github.com/lexruee/pi-switch-python",
    download_url = "https://github.com/lexruee/pi-switch-python/tarball/%s" % VERSION,
    keywords = ['switch', 'outlet sockets', 'control', 'remote', 'raspberry pi'],
    classifiers = [
        "License :: OSI Approved :: GNU Lesser General Public License v2 (LGPLv2)",
        "Development Status :: 3 - Alpha",
        "Operating System :: Other OS",
        "Intended Audience :: Developers",
        "Topic :: System :: Hardware",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3.4",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Environment :: Other Environment"
    ]
)
