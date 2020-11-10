nasm bootloader.asm -f bin -o bootloader.bin

nasm ExtendedProgram.asm -f elf64 -o ExtendedProgram.o

nasm Binaries.asm -f elf64 -o Binaries.o

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "kernel.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IDT.cpp" -o "IDT.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IO.cpp" -o "IO.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Keyboard.cpp" -o "Keyboard.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "MemoryMap.cpp" -o "MemoryMap.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "TextPrint.cpp" -o "TextPrint.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Heap.cpp" -o "Heap.o"

wsl $WSLENV/x86_64-elf-ld -T"link.ld"

copy /b bootloader.bin+kernel.bin bootloader.flp

pause