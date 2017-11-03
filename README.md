A Sega Master System emulator.

# The Hardware to Emulate

* Z80 Processor
* TMS9918a Video Display Processor
* SN79489 Sound Chip
* Controllers/Joypads


* 256 × 192 resolution, 32 colors on-screen
*  kB RAM, 16 kB VRAM

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

## Memory Control Register

Games only used bits 2 and 3 of the MCR byte(0xFFFC). Bit 3 was set if RAM was mapped into Page Slot 3 as opposed to the ROM. If RAM banking is enabled then bit 2 selects which of the 2 ram banks gets banked into slot 3. If the bit is '1' then the second ram bank is used, otherwise it will use the first.


# References

[General](http://www.codeslinger.co.uk/pages/projects/mastersystem/hardware.html)

[General](www.smspower.org)

[Hex opcodes](http://www.codeslinger.co.uk/pages/projects/mastersystem/files/z80-1.txt)

[Z80 info](http://www.codeslinger.co.uk/pages/projects/mastersystem/files/Z80.DOC)

[Z80 opcodes](http://www.geocities.com/siliconvalley/peaks/3938/z80code.htm)

[Z80 Flag Affection](http://www.z80.info/z80sflag.htm)

[Memory Mapping](http://www.smspower.org/dev/docs/wiki/MemorySystem/Mapper)

[Video Display Processor Documentation](http://www.smspower.org/dev/docs/#Video)

[Extra VDP Documentation](http://www.smspower.org/dev/docs/)

[Edge cases for VDP](http://www.smspower.org/dev/docs/#Video)

[Sound Chip](http://www.smspower.org/dev/docs/#Sound)