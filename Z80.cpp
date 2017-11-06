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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//												OPCODES
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Load immediate byte into register
void Z80::CPU_8BIT_LI(BYTE& reg) {
	m_ContextZ80.m_OpcodeCycle = 7;
	BYTE toLoad = m_ContextZ80.m_FuncPtrRead(m_ContextZ80.m_ProgramCounter);
	m_ContextZ80.m_ProgramCounter++;
	reg = toLoad;
}

void Z80::CPU_8BIT_ADD(BYTE& reg, BYTE toAdd, int cycles, bool useImmediate, bool addCarry) {

}
void Z80::CPU_8BIT_SUB(BYTE& reg, BYTE toSub, int cycles, bool useImmediate, bool subCarry) {

}
void Z80::CPU_8BIT_AND(BYTE& reg, BYTE toAnd, int cycles, bool useImmediate) {

}
void Z80::CPU_8BIT_OR(BYTE& reg, BYTE toOr, int cycles, bool useImmediate) {

}
void Z80::CPU_8BIT_XOR(BYTE& reg, BYTE toXOr, int cycles, bool useImmediate) {

}
void Z80::CPU_8BIT_CMPR(BYTE reg, BYTE toSubtract, int cycles, bool useImmediate) {

}
void Z80::CPU_8BIT_INC(BYTE& reg, int cycles) {

}
void Z80::CPU_8BIT_DEC(BYTE& reg, int cycles) {

}
void Z80::CPU_8BIT_MEM_INC(WORD address, int cycles) {

}
void Z80::CPU_8BIT_MEM_DEC(WORD address, int cycles) {

}
void Z80::CPU_8BIT_IXIY_LOAD(BYTE& store, const Z80REGISTER& re) {

}
void Z80::CPU_8BIT_MEM_IXIY_LOAD(BYTE store, const Z80REGISTER& re) {

}
void Z80::CPU_16BIT_INC(WORD& word, int cycles) {

}
void Z80::CPU_16BIT_DEC(WORD& word, int cycles) {

}
void Z80::CPU_16BIT_ADD(WORD& reg, WORD toAdd, int cycles, bool addCarry) {

}
void Z80::CPU_16BIT_SUB(WORD& reg, WORD toSub, int cycles, bool subCarry) {

}
void Z80::CPU_16BIT_LOAD(WORD& reg) {

}
void Z80::CPU_JUMP(bool useCondition, int flag, bool condition) {

}
void Z80::CPU_JUMP_IMMEDIATE(bool useCondition, int flag, bool condition) {

}
void Z80::CPU_REG_LOAD() {

}
void Z80::CPU_REG_LOAD_ROM() {

}
void Z80::CPU_LOAD_NNN(WORD reg) {

}
void Z80::CPU_NEG() {

}
void Z80::CPU_CALL(bool useCondition, int flag, bool condition) {

}
void Z80::CPU_RETURN(bool useCondition, int flag, bool condition) {

}
void Z80::CPU_RESTARTS(BYTE n) {

}
void Z80::CPU_RLC(BYTE& reg, bool isAReg) {

}
void Z80::CPU_RLC_MEM(WORD address, bool isAReg) {

}
void Z80::CPU_RRC(BYTE& reg, bool isAReg) {

}
void Z80::CPU_RRC_MEM(WORD address, bool isAReg) {

}
void Z80::CPU_DDFD_RLC(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DDFD_RRC(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DAA() {

}
void Z80::CPU_RL(BYTE& reg, bool isAReg) {

}
void Z80::CPU_RL_MEM(WORD address, bool isAReg) {

}
void Z80::CPU_RR(BYTE& reg, bool isAReg) {

}
void Z80::CPU_RR_MEM(WORD address, bool isAReg) {

}
void Z80::CPU_DDFD_RL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DDFD_RR(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_RLD() {

}
void Z80::CPU_RRD() {

}
void Z80::CPU_SLA(BYTE& reg) {

}
void Z80::CPU_SLA_MEM(WORD address) {

}
void Z80::CPU_SRA(BYTE& reg) {

}
void Z80::CPU_SRA_MEM(WORD address) {

}
void Z80::CPU_SRL(BYTE& reg) {

}
void Z80::CPU_SRL_MEM(WORD address) {

}
void Z80::CPU_SLL(BYTE& reg) {

}
void Z80::CPU_SLL_MEM(WORD address) {

}
void Z80::CPU_DDFD_SLA(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DDFD_SRA(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DDFD_SRL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_DDFD_SLL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_RESET_BIT(BYTE& reg, int bit) {

}
void Z80::CPU_DDFD_RESET_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_RESET_BIT_MEM(WORD address, int bit) {

}
void Z80::CPU_TEST_BIT(BYTE reg, int bit, int cycles) {

}
void Z80::CPU_DDFD_TEST_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_SET_BIT(BYTE& reg, int bit) {

}
void Z80::CPU_DDFD_SET_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement) {

}
void Z80::CPU_SET_BIT_MEM(WORD address, int bit) {

}
void Z80::CPU_IN(BYTE& data) {

}
void Z80::CPU_IN_IMMEDIATE(BYTE& data) {

}
void Z80::CPU_OUT(const BYTE& address, const BYTE& data) {

}
void Z80::CPU_OUT_IMMEDIATE(const BYTE& data) {

}
void Z80::CPU_OUTI() {

}
void Z80::CPU_OTIR() {

}
void Z80::CPU_OUTD() {

}
void Z80::CPU_OUTDR() {

}
void Z80::CPU_CPI() {

}
void Z80::CPU_CPIR() {

}
void Z80::CPU_CPD() {

}
void Z80::CPU_CPDR() {

}
void Z80::CPU_INI() {

}
void Z80::CPU_INIR() {

}
void Z80::CPU_IND() {

}
void Z80::CPU_INDR() {

}
void Z80::CPU_LDI() {

}
void Z80::CPU_LDIR() {

}
void Z80::CPU_DJNZ() {

}
void Z80::CPU_LDD() {

}
void Z80::CPU_LDDR() {

}
void Z80::CPU_LDA_I() {

}
void Z80::CPU_LDA_R() {

}
void Z80::CPU_REG_LOAD_NNN(WORD& reg) {

}
void Z80::CPU_EXCHANGE(WORD& reg1, WORD& reg2) {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////


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