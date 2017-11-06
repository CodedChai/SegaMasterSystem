# "The hipster console of the 8-bit era." - Gaming Historian

The SMS was Sega's much more powerful competitor to the NES. It really only found commercial success in Brazil and is still sold there today. It is known for having games such as Phantasy Star and Psycho Fox.

# The Hardware to Emulate

* Z80 Processor
* TMS9918a Video Display Processor
* SN79489 Sound Chip
* Controllers/Joypads
* 256x192, 256x224, 256 × 240(Not used for NTSC) resolutions, 32 colors on-screen, 64 colors in palette
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

### Program Counter and Stack Pointer

The program counter points to the address of the next opcode in memory to execute. The stack pointer points to the next address space where a value that gets added to the stack is stored. The stack is initialized to address 0xDFF0 so if a value is pushed to the stack it gets added to and the stack pointer gets decremented to 0xDFEF. 

Both program counter and stack pointer need to be of size WORD since the address space is 0x10000 in size. This size will also be applied to the refresh register and interrupt register.

### Opcode Prefixes

* CB prefix is a rotate, shift or bit test/set/reset instruction.
* DD prefix is executed as is, but if the HL register is supposed to be used the IX register is used instead.
* FD prefix is like the DD prefix except IY is used instead of IX.
* ED prefix, tons of undocumented EDxx instructions but most are duplicates and some behave like 2 NOP instructions. 
* DDCB prefix store the result(if any) of the operation in one of the seven general registers, the lower 3 bits of the last byte of the opcode determine which register.
* FDCB prefix is the same as DDCB except it uses IY instead of IX.

# VDP

It is a Texas Instruments TMS9918a and there is a lot to it.

### VDP Memory Map

* 0x0000 - 0x1FFF = Sprite/Tile Patterns (numbers 0-255) 
* 0x2000 - 0x37FF = Sprite/Tile Patterns (numbers 256-447)
* 0x3800 - 0x3EFF = Name Table 
* 0x3F00 - 0x3FFF = Sprite Info Table

HOWEVER, the name table and sprite info table don't always begin at address 0x3800 and 0x3F00 and can be changed. There is also Color RAM(CRAM) which holds 2 16-bit color palettes.

### Tile and Sprite Rendering

The screen is made up of tiles which represent the background. Each tile in memory is made up of 64 pixels, 8x8 sprites. To draw the background you read the contents of the name table which will give you all the tile numbers from left to right and top to bottom of the screen. Each tile number can then be looked up in the sprite/tile patterns number which gives the color of each of the 64 pixels of that sprite/tile. The screen is also made up of active objects. These sprites are usually drawn on top of the background and can be 8x8 or 16x16. It is also possible to zoom sprites which doubles the sprite size, so 8x8 becomes 16x16 and 16x16 becomes 32x32. The sprite info table specifies where on screen the sprite pattern is drawn. So the sprite pattern is looked up in the sprite info table and drawn the same way as the background.

### Overview of Registers, Modes and Ports

The VDP has 11 control registers and 1 status register. The status register is a BYTE in size but only bits 5-7 are used like so:
* Bit 7 - VSync Interrupt Pending
* Bit 6 - Sprite Overflow
* Bit 5 - Sprite Collision
* Bits 4-0 - N/A

The VDP can have its mode changed which will change how the tiles and sprites are rendered and also how the status register and the control registers are interpreted. The SMS only uses mode 2 and mode 4. In fact, every game uses mode 4 except for a game called F-16 Fighter which uses mode 2(from what I can tell).

Like all the hardware on the SMS the CPU communicates with the VDP by ports and it is the ports that the programmer uses to control the VDP. The ports are:
* 0x7E - VCounter(Read Only)
* 0x7F - HCounter(Read Only)
* 0xBE - Data Port(Read/Write)
* 0xBF - Control Port(Read/Write)

If a ROM ever tries to write to ports 0x7E-0x7F then it is actually communicating with the sound chip and not the VDP. BUT, when reading from ports 0x7E-0x7F then it is communicating with the VDP not the sound chip. Reading from port 0x7E return the VCounter. The VCounter stores the current line of the active or inactive frame that is being drawn. Reading from port 0x7F returns the HCounter. The HCounter stores which pixel of the current line is being drawn.

### Interrupts

The screen draws at either a rate of 50Hz(PAL) or 60Hz(NTSC). Every screen redraw is called a frame. Each frame has an active period and an inactive period. The active period is when the VDP is actually drawing one of the visible lines of the screen and the inactive period is when it has drawn all the visible lines of the screen. The inactive period is very important to programmers because they can program the VDP in ways they couldn't while it was in an active period, like change the vertical scroll value. So whenever the VDP leaves teh active period and enters the inactive period it tries to signal an interrupt so the ROM becomes aware of this. However, VDP interrupts can be ignored. When the VDP enters the inactive display period it sets bit-7 to show there is a VSync interrupt pending. However, a VSync interrupt is only requested if bit-7 of the status flag is set and the bit-5 of control register 1 is set. Iff both flags are set the VDP requests a VSync interrupt which the CPU can either respond to or ignore.

There is another VDP interrupt called the line interrupt. This is a value set by the programmer which counts down during the active display period and the first line of the inactive display period each time the VDP moves onto a new scanline. This is so the programmer can be informed of when the VDP starts drawing a specific scanline. If the line counter goes below zero and bit-4 of control register 0 is set then the VDP will request an interrupt and the line counter is reset to the value of register 10 when the current scanline is past the FIRST scanline of the inactive display period. If the CPU decides to ignore the VDP interrupt then the request is lost so this interrupt is either handled immediately or not at all. 


### Resolution

I will only focus on the NTSC version which has 262 scanlines.

```
Small
NTSC 256x192 
0-191 = Active Display
192-255 = Inactive Display
VCounter Values = 0x0-0xDA, 0xD5-0xFF

Medium
NTSC 256x224
0-223 = Active Display
224-255 = Inactive Display
VCounter Values = 0x0-0xEA, 0x0E5-0xFF

Large
NTSC 256x240
Doesn't work in NTSC
```

Since the VCounter is only a byte it can only store up to 256 values so in order to get 262 scanlines it has to repeat some lines. Using the small screen size as an example, when the VCounter gets to 0xDA it jumps back to 0xD5 and continues to 0xFF and this is how the extra scanlines are made to get a total of 262.

### Control Registers

As previously mentioned, there are 11 conrol registers and they only have write access. Each register is 8-bits but most bits are unused.

Register 0x0:
* Bit 7 - If set then vertical scrolling for columns 24-31 are disabled.
* Bit 6 - If set then horizontal scrolling for colums 0-1 are disabled.
* Bit 5 - If set then column 0 is set to the colour of register 0x7.
* Bit 4 - If set then line interrupt is enabled.
* Bit 3 - If set sprites are moved left by 8 pixels.
* Bit 2 - If set use Mode 4.
* Bit 1 - If set use Mode 2. Must also be set for mode4 to change screen resolution.

Register 0x1:
* Bit 6 - If set the screen is enabled.
* Bit 5 - If set vsync interrupts are enabled.
* Bit 4 - If set active display has 224 (medium) scanlines. Reg-0 bit-1 must be set.
* Bit 3 - If set active display has 240 (large) scanlines. Reg-0 bit-1 must be set.
* Bit 1 - If set sprites are 16x16 otherwise 8x8.
* Bit 0 - If set sprites are zoomed (double sprite's size).

Register 0x2:
* Bit 3 - Bit 13 of the name base table address.
* Bit 2 - Bit 12 of the name base table address.
* Bit 1 - Bit 11 of the name base table address if resolution is "small" otherwise unused.

Register 0x3 and 0x4:
* Unused

Register 0x5:
* Bit 6 - Bit 13 of sprite info base table
* Bit 5 - Bit 12 of sprite info base table
* Bit 4 - Bit 11 of sprite info base table
* Bit 3 - Bit 10 of sprite info base table
* Bit 2 - Bit  9 of sprite info base table
* Bit 1 - Bit  8 of sprite info base table

Reister 0x6:
* Bit 2 - If set sprites use tiles in memory 0x2000 (tiles 256..511), else memory 0x0 (tiles 0 - 256).

Register 0x7:
* Bits 3-0 - Defines the color to use for the overscan order.

Register 0x8:
* The entire 8 bit register is the Background X Scrolling position.

Register 0x9:
* The entire 8 bit register is the Background Y Scrolling position.

Register 0xA:
* The entire 8 bit register is what the line counter should be set to.

### Rendering in Mode 4

Sprites are rendered before the backround. The VDP is limited to 8 sprites on any snaline. There are 64 sprites available to draw which are referenced in the sprite attribute table. Sprites can not be scrolled. It is drawn one line at a time. 

Rendering backgrounds is very similar to rendering sprites but there's priorities, scrolling and masking. 

# Joypads

Each joypad button has its own bit in a read only joypad status register. There are two joypad status registers which the game can read. PortA is port number 0xDC and is mirrored at 0xC0. PortB is port number 0xDD and is mirrored at 0xC1.

PortA:
* Bit 7 - Joypads 2 down button 
* Bit 6 - Joypads 2 up button
* Bit 5 - Joypads 1 Fire B
* Bit 4 - Joypads 1 Fire A
* Bit 3 - Joypads 1 Right Button
* Bit 2 - Joypads 1 Left Button
* Bit 1 - Joypads 1 Down Button
* Bit 0 - Joypads 1 Up Button

PortB:
* Bit 7 - Unused 
* Bit 6 - Unused 
* Bit 5 - Unused 
* Bit 4 - Reset Button
* Bit 3 - Joypads 2 Fire B
* Bit 2 - Joypads 2 Fire A
* Bit 1 - Joypads 2 Right Button
* Bit 0 - Joypads 2 Left Button

# Interrupts 

The SMS has 3 hardware interrupts, when a piece of hardware signals to the VPU to stop doing what it's currently doing to do something that is deemed immediately important. The interrupts are VSync, line counter and the reset interrupt. The first two can be ignored by the CPU whereas the reset interrupt is always accepted. 

# PSG

The PSG is a Texas Instruments SN79489. The sound chip has 4 different channels, three tone channels and one noise channel. Each channel can have a different volume and different frequency. To change the volumes and frequency of the channels, data is written to port 0x7F which is also mirrored to 0x7E.

The clock is the same as the Z80 and each channel has a counter which is set to its frequency. Every 224kHz each channels counter is decremented and then the output of all channels is combined and added to the playback buffer. When one of the counters reaches - then it is reset to the value of the channels frequency and the polarity of the output for this channel is changed.

### Square Waves

Square waves are pretty simple, they either output 1 or -1 if they're signed or output 1 or o if they're unsigned. However, using signed square waves will be simpler since you just have to add up the values of the 4 channels. You just have to make sure that you multiply each channel by it's volume before adding them together.

### PSG Registers

Each channel has 2 registers associated with it. The first channel register is the volume which is a 4-bit register. The second channel register is the tone register which is a 10-bit register that holds the frequency. However, on the noise channel the tone register is ounly 4-bits. The volume registers are set to 0xF and the tone registers are set to 0x0 on startup.

### PSG Channel Volume

0x0 actually means full volume and 0xF is muted. The volume increments by 2db. The volume register should be 8-bits even though only the lower 4-bits are used. The most common value type for the playback buffer are signed 16-bit samples. The minimum would be -32768 and the maximum would be 32767. To ensure we don't overflow the playback buffer the volume channel should max out at 8000. This will guarantee that the playback buffer will never get overflown.

### Writing Data to PSG

Sound data is written to the PSG through ports 0x7F and 0x7E. The PSG has a latch which is the current register where the data byte is designed for. The initially lathed register is Channel0s tone register. The data byte written takes one of two forms. Form 1 changes the current latched register and updates its data. Form 2 is data intended to be written to the currently latched register. The 2 different data types should be interpreted like so:

* Type 1 - 1ccrdddd
* Type 2 - 0xdddddd

So you can identify the two data types by bit-7.

#### Type 1

If the data byte being written to the PSG port has bit-7 set then this is how the data should be interpreted. This data byte is designed to update the currently latched register and then update its data. Bits 6-5 represent which channel needs to be latched. Bit-4 is whther you need to latch a volume(1) or tone(0) register. The remaining 4-bits are the data that updates the LOWER 4-bits of the newly latched register. So if the newly latched register is a colume register then the lower 4-bits of the 8-bit register is updated and the upper 4-bits are left unchanged, the entire 4-bits of the noise register would get updated and the upper 6-bits of the 10-bit tone register would go unchanged.

#### Type 2

If the currently latched register is a tone register then the lower 6-bits of the data byte is used to update the upper 6-bits of the 10-bit tone register leaving the bottom 4-bits unchanged. If it is latched to a noise or volume register it only uses the lower 4 bits to update it.

# References

[General - Most Used](http://www.codeslinger.co.uk/pages/projects/mastersystem/hardware.html)

[Basically Everything is Here](www.smspower.org)

[Hex opcodes](http://clrhome.org/table/)

[Z80 Manual](http://www.smspower.org/uploads/Development/z80cpu_um.zip)

[Undocumented Z80 Info](http://www.smspower.org/uploads/Development/z80-documented.pdf?sid=d5d37285c1ed4e0ad0ffe94266d31197)

[Z80 Opcodes](http://www.z80.info/z80oplist.txt)

[Random Blog That May Be Useful](http://floooh.github.io/2016/07/12/z80-rust-ms1.html)

[Memory Mapping](http://www.smspower.org/dev/docs/wiki/MemorySystem/Mapper)

[Video Display Processor Documentation](http://www.smspower.org/dev/docs/#Video)

[Extra VDP Documentation](http://www.smspower.org/dev/docs/)

[Edge cases for VDP](http://www.smspower.org/dev/docs/#Video)

[Sound Chip](http://www.smspower.org/dev/docs/#Sound)
