#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, subprocess, sys

from distutils.core import setup
from distutils.command.build import build
from distutils.command.clean import clean
from distutils.command.install import install



UNITEX_INC = os.path.expandvars("$UNITEX_INC")
if UNITEX_INC == "$UNITEX_INC":
    sys.stderr.write( "You need to specify the UNTIEX_INC variable (i.e. Unitex C++ src directory)!\n" )
    sys.stderr.write( "  -> e.g.: UNITEX_INC=/path/to/unitex/Src/C++ python setup.py cmd\n" )
    sys.exit(1)
UNITEX_INC = os.path.abspath(UNITEX_INC)



class CustomBuild(build):

    def run(self):
        command = "cd %s && make 64BITS=yes LIBRARY=yes" % os.path.join(UNITEX_INC, "build")
        
        try:
            process = subprocess.Popen(command, stderr=subprocess.PIPE, shell=True)
        except Exception as e:
            sys.stderr.write("Error in command: %s\n" % command)
            raise e
        
        process.wait()

        if process.returncode != 0:
            raise OSError(process.stderr.read())
        build.run(self)



class CustomClean(clean):

    def run(self):
        command = "cd %s && make clean" % os.path.join(UNITEX_INC, "build")

        try:
            process = subprocess.Popen(command, stderr=subprocess.PIPE, shell=True)
        except Exception as e:
            sys.stderr.write("Error in command: %s\n" % command)
            raise e
        
        process.wait()

        if process.returncode != 0:
            raise OSError(process.stderr.read())
        clean.run(self)



class CustomInstall(install):

    def run(self):
        library = None

        if sys.platform == "darwin":
            library = "libunitex.dylib"
        elif sys.platform == "linux2":
            library = "libunitex.so"
        else:
            sys.stderr.write("Plateform '%s' not supported...\n" % sys.platform)
            sys.exit(1)

        command = "cd %s && cp %s /usr/local/lib" % (os.path.join(UNITEX_INC, "bin"), library)

        try:
            process = subprocess.Popen(command, stderr=subprocess.PIPE, shell=True)
        except Exception as e:
            sys.stderr.write("Error in command: %s\n" % command)
            raise e
        
        process.wait()

        if process.returncode != 0:
            raise OSError(process.stderr.read())
        install.run(self)



setup(
    name = "unitex",
    version = "1.0",
    description = "Python 3 binding for the Unitex library",
    long_description = open('README').read(),

    author = "Patrick Watrin",
    author_email = "patrick.watrin@gmail.com",

    # https://pypi.python.org/pypi?%3Aaction=list_classifiers
    classifiers = [
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3 :: Only",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Topic :: Scientific/Engineering :: Information Analysis",
    ],
    keywords = "Unitex, Finite-States Transducers, Natural Language Processing",

    license = "MIT",
    install_requires = [
        # TO FILL
    ],

    packages = ["unitex"],
    package_dir = {'unitex': 'unitex'},

    data_files = [
    ],

    cmdclass = {
        "build": CustomBuild,
        "clean": CustomClean,
        "install": CustomInstall
    }
)
