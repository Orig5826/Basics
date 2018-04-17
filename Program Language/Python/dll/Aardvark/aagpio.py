# !/bin/env python
#==========================================================================
# (c) 2004-2006  Total Phase, Inc.
#--------------------------------------------------------------------------
# Project : Aardvark Sample Code
# File    : aagpio.py
#--------------------------------------------------------------------------
# Perform some simple GPIO operations with a single Aardvark adapter.
#--------------------------------------------------------------------------
# Redistribution and use of this file in source and binary forms, with
# or without modification, are permitted.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#==========================================================================

#==========================================================================
# IMPORTS
#==========================================================================
from __future__ import division, with_statement, print_function
import sys
import time
from aardvark_py import *


#==========================================================================
# MAIN PROGRAM
#==========================================================================
if (len(sys.argv) < 2):
    print("usage: aagpio PORT")
    sys.exit()

port = int(sys.argv[1])

# Open the device
(handle, aaext) = aa_open_ext(port)
if (handle <= 0):
    print("Unable to open Aardvark device on port %d" % port)
    print("Error code = %d" % handle)
    sys.exit()

print("Opened Aardvark adapter; features = 0x%02x" % aaext.features)

# Configure the Aardvark adapter so all pins
# are now controlled by the GPIO subsystem
aa_configure(handle, AA_CONFIG_GPIO_ONLY)

# Make sure the charge has dissipated on those lines
aa_gpio_set(handle, 0x00)
aa_gpio_direction(handle, AA_GPIO_SS)

for i in range(0, 10):
    print(i, end=' ', flush=True)
    aa_gpio_set(handle, AA_GPIO_SS)
    time.sleep(0.25)
    aa_gpio_set(handle, 0x00)
    time.sleep(0.25)


# Close the device
aa_close(handle)
