[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp PROGRAM_SPACE

jmp $

%include "source/x86_64asm/Print.asm"
%include "source/x86_64asm/ReadFromDisk.asm"

times 510-($-$$) db 0

dw 0xaa55
