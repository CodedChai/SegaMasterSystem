#pragma once
#ifndef _Z80_H
#define _Z80_H
#include "Defines.h"

#define FLAG_S 7	// Sign bit-7
#define FLAG_Z 6	// Zero bit-6
#define FLAG_H 4	// Half Carry bit-4
#define FLAG_PV 2	// Parity or Overflow bit-2
#define FLAG_N 1	// Subtract bit-1
#define FLAG_C 0	// Carry bit-0

namespace SMS {
	union Z80REGISTER {
		WORD reg ;
		struct {
			BYTE lo;
			BYTE hi;
		};
	};

	struct CONTEXTZ80 {
		Z80REGISTER m_RegisterAF;
		Z80REGISTER m_RegisterAFShadow;
		Z80REGISTER m_RegisterBC;
		Z80REGISTER m_RegisterBCShadow;
		Z80REGISTER m_RegisterDE;
		Z80REGISTER m_RegisterDEShadow;
		Z80REGISTER m_RegisterHL;
		Z80REGISTER m_RegisterHLShadow;
		Z80REGISTER m_RegisterIX;
		Z80REGISTER m_RegisterIY;
		Z80REGISTER m_StackPointer;
		WORD m_ProgramCounterStart;
		WORD m_ProgramCounter;

	};
}


#endif // !_Z80_H
