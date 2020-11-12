OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT
(
objects_and_binaries/ExtendedProgram.o
objects_and_binaries/kernel.o
objects_and_binaries/IDT.o
objects_and_binaries/IO.o
objects_and_binaries/MemoryMap.o
objects_and_binaries/Print.o
objects_and_binaries/Keyboard.o
objects_and_binaries/Heap.o
objects_and_binaries/Memory.o
objects_and_binaries/binaries.o
objects_and_binaries/shell.o
objects_and_binaries/BonusFunctions.o
objects_and_binaries/commands.o
)

OUTPUT
(
objects_and_binaries/kernel.bin
)

SECTIONS
{
	. = 0x8000;
	
	.text : ALIGN(0x1000)
	{
	*(.text)
	}
	
	.idt BLOCK(0x1000) : ALIGN(0x1000)
	{
	_idt = .;
	. = . + 0x1000;
	}
	
	.data : ALIGN(0x1000)
	{
	*(.data)
	}
	
	.rodata : ALIGN(0x1000)
	{
	*(.rodata)
	}
	
	.bss : ALIGN(0x1000)
	{
	*(COMMON)
	*(.bss)
	}
}
