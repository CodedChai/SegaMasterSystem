"The hipster console of the 8-bit era." - Gaming Historian

# The Hardware to Emulate

* Z80 Processor
* TMS9918a Video Display Processor
* SN79489 Sound Chip
* Controllers/Joypads


* 256 × 192 resolution, 32 colors on-screen
* 8 kB RAM, 16 kB VRAM

# Timing

* Main clock - 10.738580 MHz
* Z80 Processor Clock & Sound Clock - 3.58 MHz (Main clock/3)
* VDP Clock - 5.36 MHz (Main clock/2)
* 60fps lock required

# Ports

How the 4 main processors interact. They use the Z80's IN and OUT instructions.

* 0x7E : Reading: returns VDP V counter. Writing: Writes data to Sound Chip.
* 0x7F : Reading: returns VDP H counter. Writing: Writes data to Sound Chip (same as above).
* 0xBE : Reading: reads VDP data port. Writing: Writes VDP data port.
* 0xBD = 0xBF : Reading: Gets VDP status. Writing: Writes to VDP control port.
* 0xC0 = 0xDC : Reading: Reads joypad 1. Writing: N/A
* 0xC1 = 0xDD : Reading: Reads joypad 2. Writing: N/A

# Memory

* 0x0000-0x3FFF : ROM Slot 1
* 0x4000-0x7FFF : ROM Slot 2
* 0x8000-0xBFFF : ROM Slot 3 / RAM Slot    RAM banking takes priority over ROM banking.
* 0xC000-0xDFFF : RAM
* 0xE000-0xFFFF : Mirrored RAM

It is important to remember that even though these pages can be swapped in and out at any point the first 0x400 bytes of slot 1 does not get paged out. This is because the interrupt handler routines are at this address space and they need to always be present so interrupts can get handled correctly. This means that address range 0x0-0x400 is always data of page0 0x0-0x400.

The memory mapping registers are address 0xFFFC-0xFFFF

* 0xFFFC: Memory Control Register
* 0xFFFD: Writing a value to this address maps that values page into slot 1
* 0xFFFE: Writing a value to this address maps that values page into slot 2
* 0xFFFF: Writing a value to this address maps that values page into slot 3

### Memory Control Register

Games only used bits 2 and 3 of the MCR byte(0xFFFC). Bit 3 was set if RAM was mapped into Page Slot 3 as opposed to the ROM. If RAM banking is enabled then bit 2 selects which of the 2 ram banks gets banked into slot 3. If the bit is '1' then the second ram bank is used, otherwise it will use the first.

# Z80

An 8-bit microprocessor which has 8 standard registers, 8 shadow registers, 2 index registers, 1 refresh register and 1 interrupt vector register. It also includes stack, program counter and 8 flags, although only 6 of the flags were used in the SMS's Z80.

### The Registers

The 8 standard 8-bit registers:
* A - Accumulator
* B - General Purpose
* C - General Purpose
* D - General Purpose
* E - General Purpose
* F - Flag Register
* H - Address Register
* L - Address Register

However, the registers can be paired to form 4 sets of 16 bit registers. The pairings are:
* AF
* BC
* DE
* HL - Commonly used as a pair since the Z80 address space is 16-bit

There are also 8 shadow registers that can not be modified directly by any Z80 instruction. They are named the same as the standrd registers but with a ' after the letter and can be paired in the same way. Their purpose is to be exchanged with their corresponding standard register. So you could swap standard register AF with shadow register AF'.

The 2 index registers, IX and IY, are used with two opcode prefixes which replaces the registes H and L for instructions that use registers HL. For example, ADD HL, HL would become ADD IX, IX for one opcode prefix and ADD IY, IY for the other. When an instruction uses HL for memory access an 8-bit offset is added to IX and IY.

The refresh register is a counter that gets incremented everytime an opcode gets fetched. Usually used to create random numbers.

The interrupt register works with interrupt mode 2.

### The Flags

6 bits in the 8-bit flag register represents a flag.

* Bit 7 - (S) Sign Flag: The sign flag is simply a copy of the 7th bit of the result of a math Z80 instruction. However with some 16bit instructions it will be a copy of the 15th bit of the resulting operation.
* Bit 6 - (Z) Zero Flag: The zero flag is set when the result of an operation is zero.
* Bit 5 - N/A
* Bit 4 - (H) Half Carry Flag: The Half carry flag is set if a subtract operation carried from bit 4 to bit 3 or, or with an 16 bit operation carried from bit 12 to 11. With addition operations it is set if carried from bit 3 to 4 or with 16 bit addition 11 to 12.
* Bit 3 - N/A
* Bit 2 - (P/V) Parity or Overflow Flag: The Parity or Overflow flag has two meanings. Some instructions use the parity flag which means it gets set if the result of the operation has an even number of bits set. The overflow flag is used by some instructions when the 2-complement of the result does not fit within the register.
* Bit 1 - (N) Subtract Flag: The subtract flag is simply set when the instruction is a subtraction.
* Bit 0 - (C) Carry flag: The carry flag is set when the instruction overflows its upper or lower limits.

# References

[General](http://www.codeslinger.co.uk/pages/projects/mastersystem/hardware.html)

[Basically Everything](www.smspower.org)

[Hex opcodes](http://www.codeslinger.co.uk/pages/projects/mastersystem/files/z80-1.txt)

[Z80 info](http://www.codeslinger.co.uk/pages/projects/mastersystem/files/Z80.DOC)

[Z80 opcodes](http://www.geocities.com/siliconvalley/peaks/3938/z80code.htm)

[Z80 Flag Affection](http://www.z80.info/z80sflag.htm)

[Memory Mapping](http://www.smspower.org/dev/docs/wiki/MemorySystem/Mapper)

[Video Display Processor Documentation](http://www.smspower.org/dev/docs/#Video)

[Extra VDP Documentation](http://www.smspower.org/dev/docs/)

[Edge cases for VDP](http://www.smspower.org/dev/docs/#Video)

[Sound Chip](http://www.smspower.org/dev/docs/#Sound)