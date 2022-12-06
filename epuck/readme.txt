Tiny Interface Howto
--------------------
You will communicate with the existing Epuck firmware via a
serial protocol over bluetooth. Some commands can be found here:
http://www.amd.e-technik.uni-rostock.de/ma/hinki/cpp/epuck.html
To program the Epuck you need to know the interpretation and valid 
ranges of the interface function's parameters and return values.
Information can be found at
http://www.gctronic.com/doc/index.php/E-Puck
or in the source code of the epuck firmware at
http://gna.org/projects/e-puck/

Unfortunaley, no sufficient information on this topic seems to be 
available. So you will have to play around with it and find out for
yourself. Some sparse information can be found in the sections of 
"www.e-puck.org -> Robot".

Prerequisites
-------------
In order to compile the test program, you need
libqt4-dev and libbluetooth-dev packages on a debian based distribution.
These packages are already installed in the pool 1216.

Compile the sources
-------------------
Simply type make.
There is a makefile that does the right thing.
(something like qmake -project LIBS+=-lbluetooth)
required packages on debian: libbluetooth-dev

Interface implementations
-------------------------
On order to work without a robot at hand,
use the EpuckDummy class provided in EpuckDummy.hpp.
All input is ignored, all output is set to zero.

For the real epuck, there are two implementations:
1. blocking io: if_block.hpp (default)
2. non-blocking io: if_nonblock.hpp
Either pick one, write your own, or stick with the defaults in
test/test.cpp

Errors
------
In the case of infrequent connection errors,
1. recharge the battery
2. replace the bluetooth adapter
3. ask for help
