nasm source/x86_64asm/bootloader.asm -f bin -o objects_and_binaries/bootloader.bin

nasm source/x86_64asm/ExtendedProgram.asm -f elf64 -o objects_and_binaries/ExtendedProgram.o

nasm source/x86_64asm/bin.asm -f elf64 -o objects_and_binaries/binaries.o

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/kernel.cpp" -o "objects_and_binaries/kernel.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/IDT.cpp" -o "objects_and_binaries/IDT.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/IO.cpp" -o "objects_and_binaries/IO.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/Keyboard.cpp" -o "objects_and_binaries/Keyboard.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/MemoryMap.cpp" -o "objects_and_binaries/MemoryMap.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/Print.cpp" -o "objects_and_binaries/Print.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/Heap.cpp" -o "objects_and_binaries/Heap.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/Memory.cpp" -o "objects_and_binaries/Memory.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/shell.cpp" -o "objects_and_binaries/shell.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/BonusFunctions.cpp" -o "objects_and_binaries/BonusFunctions.o"

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "source/C++/commands.cpp" -o "objects_and_binaries/commands.o"

wsl $WSLENV/x86_64-elf-ld -T"link.ld"

wsl /bin/cat objects_and_binaries/bootloader.bin objects_and_binaries/kernel.bin > product/CCOS.iso
