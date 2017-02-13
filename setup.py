#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
PiSwitch - A Python wrapper around the rc-switch library for the Raspberry Pi
Copyright (c) 2015-2017 Alexander Rueedlinger.  All right reserved.

    Project home: https://github.com/lexruee/pi-switch-python

The source code of rc-switch library can be found at:
    Project home: https://github.com/sui77/rc-switch

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
"""

import sys
import os
from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.test import test
from setuptools import Command
from distutils.sysconfig import customize_compiler
from setuptools.dist import Distribution


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


class CustomCleanCommand(Command):
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        os.system('rm -vrf ./build ./dist ./*.egg-info ./*.egg ./*.so')


class CustomTestCommand(test):

    def finalize_options(self):
        test.finalize_options(self)
        self.test_args = ['--pyargs', 'tests']
        self.test_suite = True

    def run_tests(self):
        import pytest
        err = pytest.main(self.test_args)
        sys.exit(err)


class BinaryDistribution(Distribution):

    def is_pure(self):
        return False


VERSION = "0.5.0.dev"

setup(
    name="pi_switch",
    version = VERSION,
    license='LGPLv2',
    platforms='',

    packages = find_packages(exclude=["*.tests", "*.tests.*", "tests.*", "tests"]),
    scripts = [],
    tests_require=['pytest'],
    package_data={},

    cmdclass = {
        'build_ext': CustomBuildExt,
        'clean': CustomCleanCommand,
        'test': CustomTestCommand
    },
    ext_modules = [
        Extension("_pi_switch",
                  sources = [
                      "wrapper/rc-switch/RCSwitch.cpp",
                      "wrapper/PiSwitch.cpp",
                      "wrapper/Binding.cpp"
                  ],
                  libraries = ["wiringPi"],
                  extra_compile_args=[
                      '-std=c++11', '-DRPI', '-Wall', '-Wno-write-strings'
                  ],
                  language="c++")
    ],

    include_package_data = True,
    distclass=BinaryDistribution,

    entry_points={},

    description = "Pi Switch is a Python wrapper around the rc-switch library for the Raspberry Pi.",
    author = "Alexander Rüedlinger",
    author_email = "a.rueedlinger@gmail.com",
    url = "https://github.com/lexruee/pi-switch-python",
    download_url = "https://github.com/lexruee/pi-switch-python/tarball/{}".format(VERSION),
    keywords = ['switch', 'outlet sockets', 'control', 'remote', 'raspberry pi'],
    classifiers = [
        "License :: OSI Approved :: GNU Lesser General Public License v2 (LGPLv2)",
        "Development Status :: 3 - Alpha",
        "Operating System :: Other OS",
        "Intended Audience :: Developers",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3.4",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: System :: Hardware",
        "Topic :: Home Automation",
        "Operating System :: POSIX :: Linux"
    ]
)
