DetectCPUid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << 21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	xor eax, ecx
	jz noCPUid
	
	ret

DetectLongMode:
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz NoLongMode
	ret
	
;rlly no cpuid or long mode bruh

NoLongMode:
	hlt

noCPUid:
	hlt
