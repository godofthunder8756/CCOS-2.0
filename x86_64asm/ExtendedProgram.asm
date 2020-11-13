jmp EThirtyTwoBitMode

%include "source/x86_64asm/GlobalDescriptorTable.asm"
%include "source/x86_64asm/Print.asm"
%include "source/x86_64asm/detectMemory.asm"

EThirtyTwoBitMode:
	call DetectMemory
	call EnableA20
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:ThirtyTwoBitMode
	
EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[bits 32]

%include "source/x86_64asm/CPUid.asm"
%include "source/x86_64asm/paging.asm"	

ThirtyTwoBitMode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	
	call DetectCPUid
	call DetectLongMode
	call SetUpPaging
	call EditGDT
	jmp codeseg:SixtyFourBitMode

;well boys we did it, 64 bits, les gooooo

[bits 64]
[extern _start]

%include "source/x86_64asm/IDT.asm"

SixtyFourBitMode:
	mov edi, 0xb8000
	mov rax, 0x1f201f201f201f20
	mov ecx, 500
	rep stosq
	call ActivateSSE
	call _start
	jmp $

ActivateSSE:
	mov rax, cr0
	and ax, 0b11111101
	or ax, 0b00000001
	mov cr0, rax
	
	mov rax, cr4
	or ax, 0b1100000000
	mov cr4, rax
	
	ret

;times 32768-($-$$) db 0
