#include "Z80.h"
#include <memory.h>
#include <stdio.h>

Z80::Z80(void) {
	memset(&m_DAATable, 0, sizeof(m_DAATable));
	memset(&m_ZSPTable, 0, sizeof(m_ZSPTable));
	InitDAATable();
}

Z80::~Z80(void)
{

}

WORD Z80::ReadWord() const
{
	WORD result = m_ContextZ80.m_FuncPtrRead(m_ContextZ80.m_ProgramCounter + 1);
	result = result << 8;
	result |= m_ContextZ80.m_FuncPtrRead(m_ContextZ80.m_ProgramCounter);
	return result;
}

void Z80::PushWordOntoStack(WORD word)
{
	BYTE hi = word >> 8;
	BYTE lo = word & 0xFF;
	m_ContextZ80.m_StackPointer.reg--;
	m_ContextZ80.m_FuncPtrWrite(m_ContextZ80.m_StackPointer.reg, hi);
	m_ContextZ80.m_StackPointer.reg--;
	m_ContextZ80.m_FuncPtrWrite(m_ContextZ80.m_StackPointer.reg, lo);
}

WORD Z80::PopWordOffStack()
{
	WORD word = m_ContextZ80.m_FuncPtrRead(m_ContextZ80.m_StackPointer.reg + 1) << 8;
	word |= m_ContextZ80.m_FuncPtrRead(m_ContextZ80.m_StackPointer.reg);
	m_ContextZ80.m_StackPointer.reg += 2;
	return word;
}

void Z80::IncreaseRReg()
{
	if ((m_ContextZ80.m_RegisterR & 127) == 127)
		m_ContextZ80.m_RegisterR = m_ContextZ80.m_RegisterR & 128;
	else
		m_ContextZ80.m_RegisterR++;
}

void Z80::ExecuteOpcode(const BYTE& opcode)
{
	IncreaseRReg();
	switch (opcode) {

	default:
		printf("Unimplemented opcode %X\n", opcode);
		break;
	}
}

void Z80::InitDAATable() {
	// Initialize z, s, v flags
	for (int i = 0; i < 256; ++i)
	{
		BYTE zFlag = (i == 0) ? 0x40 : 0;
		BYTE sFlag = i & 0x80;
		BYTE vFlag = 0x04;
		for (int v = 128; v != 0; v >>= 1)
		{
			if (i & v)
				vFlag ^= 0x04;
		}
		m_ZSPTable[i] = zFlag | sFlag | vFlag;
	}

}