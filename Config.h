#pragma once
#ifndef _CONFIG_H
#define _CONFIG_H

typedef unsigned char BYTE;
typedef signed char SIGNED_BYTE;
typedef unsigned short int WORD;
typedef signed short int SIGNED_WORD;

#define ONE_MB				0x100000		// 1,048,576	 1MB
#define SIXTY_FOUR_KB		0x10000			//    65,536	64KB
#define FORTYEIGHT_KB		0xC000			//    49,152	48KB
#define THIRTY_TWO_KB		0x8000			//    32,768	32KB
#define SIXTEEN_KB			0x4000			//    16,384	16KB
#define EIGHT_KB			0x2000			//     8,192	 8KB
#define FOUR_KB				0x1000			//     8,096	 4KB
#define MAX_FILENAME		32

template< typename typeData >
inline bool TestBit(typeData inData, int inBitPosition)
{
	typeData lMsk = 1 << inBitPosition;
	return (inData & lMsk) ? true : false;
}

template< typename typeData >
inline typeData BitGet(typeData inData, int inBitPosition)
{
	typeData lMsk = 1 << inBitPosition;
	return lMsk;
}

template< typename typeData >
inline typeData BitGetVal(typeData inData, int inBitPosition)
{
	typeData lMsk = 1 << inBitPosition;
	return (inData & lMsk) ? 1 : 0;
}

template< typename typeData >
inline typeData BitSet(typeData inData, int inBitPosition)
{
	typeData lMsk = 1 << inBitPosition;
	inData |= lMsk;
	return inData;
}

template< typename typeData >
inline typeData BitReset(typeData inData, int inBitPosition)
{
	typeData lMsk = 1 << inBitPosition;
	inData &= ~lMsk;
	return inData;
}

template< typename typeData >
int BitCount(typeData inData, int totalBits)
{
	int res = 0;
	for (int i = 0; i < totalBits; i++)
	{
		if (TestBit(inData, i))
			res++;
	}
	return res;
}

#endif
