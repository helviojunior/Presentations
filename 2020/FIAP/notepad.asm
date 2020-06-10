[BITS 32]

_start:
	xor eax,eax
	push eax
	push 0x20657865
	push 0x2e646170
	push 0x65746f6e
	push esp
	
	mov eax, 0x72741a4f
	call eax