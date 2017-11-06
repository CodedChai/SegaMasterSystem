#ifndef _DEFINES_H_
#define _DEFINES_H_

#define ONE_MB				0x100000		// 1,048,576	 1MB
#define SIXTY_FOUR_KB		0x10000			//    65,536	64KB
#define FORTYEIGHT_KB		0xC000			//    49,152	48KB
#define THIRTY_TWO_KB		0x8000			//    32,768	32KB
#define SIXTEEN_KB			0x4000			//    16,384	16KB
#define EIGHT_KB			0x2000			//     8,192	 8KB
#define FOUR_KB				0x1000			//     8,096	 4KB

#define MAX_FILENAME		32

namespace SMS
{
	// Config
	typedef unsigned char BYTE;
	typedef signed char SIGNED_BYTE;
	typedef unsigned short int WORD;
	typedef signed short int SIGNED_WORD;

	// Master System
	static const int WINDOWWIDTH = 256;
	static const int WINDOWHEIGHT = 192;
	static const int SCREENSCALE = 1;

	// Emulator
	static const	long long	MACHINE_CLICKS = 10738635;
	static const	int			CPU_CYCLES_TO_MACHINE_CLICKS = 3;
}

#endif//_DEFINES_H_