#pragma once
#ifndef _Z80_H
#define _Z80_H
#include "Config.h"

typedef BYTE(*Z80ReadMemory)(WORD);
typedef void(*Z80WriteMemory)(WORD, BYTE);
typedef BYTE(*Z80IOReadMemory)(BYTE);
typedef void(*Z80IOWriteMemory)(BYTE, BYTE);

#define FLAG_S 7	// Sign bit-7
#define FLAG_Z 6	// Zero bit-6
#define FLAG_H 4	// Half Carry bit-4
#define FLAG_PV 2	// Parity or Overflow bit-2
#define FLAG_N 1	// Subtract bit-1
#define FLAG_C 0	// Carry bit-0

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
	BYTE m_RegisterI;
	BYTE m_RegisterR;

	WORD m_ProgramCounterStart;
	WORD m_ProgramCounter;
	BYTE m_CartridgeMemory[ONE_MB];
	BYTE m_InternalMemory[ONE_MB];
	BYTE m_OpcodeCycle;
	Z80ReadMemory		m_FuncPtrRead;
	Z80WriteMemory		m_FuncPtrWrite;
	Z80IOReadMemory		m_FuncPtrIORead;
	Z80IOWriteMemory	m_FuncPtrIOWrite;

	bool m_Halted;
	bool m_IFF1; // Interrupt flip flop 1
	bool m_IFF2; // Interrupt flip flop 2
	bool m_EIPending; // Enable interrupts
	int m_InterruptMode;
	bool m_NMI;
	bool m_NMIServicing;
};

class Z80 {
public:
	Z80(void);
	~Z80(void);

	int ExecuteNextOpcode();
	void PushWordOntoStack(WORD address);
	void IncreaseRReg();
	CONTEXTZ80* GetContext() { return &m_ContextZ80 };

private:
	CONTEXTZ80		m_ContextZ80;
	void ExecuteOpcode(const BYTE& opcode);
	void ExecuteCBOpcode();
	void ExecuteDDFDCBOpcode(bool isDD);
	void ExecuteEDOpcode();
	void ExecuteDDFDOpcode(bool isDD);

	WORD ReadWord() const;
	WORD PopWordOffStack();
	void LogInstanceInfo(BYTE opcode, const char* subset, bool showmnemonic);
	WORD GetIXIYAddress(WORD value);
	void InitDAATable();

	WORD m_DAATable[0x800];
	BYTE m_ZSPTable[256];

	// Instructions
	void CPU_8BIT_LI(BYTE& reg);
	void CPU_REG_LOAD(BYTE& reg, BYTE load);
	void CPU_REG_LOAD_ROM(BYTE& reg, WORD address);
	void CPU_8BIT_ADD(BYTE& reg, BYTE toAdd, int cycles, bool useImmediate, bool addCarry);
	void CPU_8BIT_SUB(BYTE& reg, BYTE toSub, int cycles, bool useImmediate, bool subCarry);
	void CPU_8BIT_AND(BYTE& reg, BYTE toAnd, int cycles, bool useImmediate);
	void CPU_8BIT_OR(BYTE& reg, BYTE toOr, int cycles, bool useImmediate);
	void CPU_8BIT_XOR(BYTE& reg, BYTE toXOr, int cycles, bool useImmediate);
	void CPU_8BIT_CMPR(BYTE reg, BYTE toSubtract, int cycles, bool useImmediate);
	void CPU_8BIT_INC(BYTE& reg, int cycles);
	void CPU_8BIT_DEC(BYTE& reg, int cycles);
	void CPU_8BIT_MEM_INC(WORD address, int cycles);
	void CPU_8BIT_MEM_DEC(WORD address, int cycles);
	void CPU_8BIT_IXIY_LOAD(BYTE& store, const Z80REGISTER& reg);
	void CPU_8BIT_MEM_IXIY_LOAD(BYTE store, const Z80REGISTER& reg);
	void CPU_16BIT_INC(WORD& word, int cycles);
	void CPU_16BIT_DEC(WORD& word, int cycles);
	void CPU_16BIT_ADD(WORD& reg, WORD toAdd, int cycles, bool addCarry);
	void CPU_16BIT_SUB(WORD& reg, WORD toSub, int cycles, bool subCarry);
	void CPU_16BIT_LOAD(WORD& reg);
	void CPU_JUMP(bool useCondition, int flag, bool condition);
	void CPU_JUMP_IMMEDIATE(bool useCondition, int flag, bool condition);
	void CPU_LOAD_NNN(WORD reg);
	void CPU_NEG();
	void CPU_CALL(bool useCondition, int flag, bool condition);
	void CPU_RETURN(bool useCondition, int flag, bool condition);
	void CPU_RESTARTS(BYTE n);
	void CPU_RLC(BYTE& reg, bool isAReg);
	void CPU_RLC_MEM(WORD address, bool isAReg);
	void CPU_RRC(BYTE& reg, bool isAReg);
	void CPU_RRC_MEM(WORD address, bool isAReg);
	void CPU_DDFD_RLC(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DDFD_RRC(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DAA();
	void CPU_RL(BYTE& reg, bool isAReg);
	void CPU_RL_MEM(WORD address, bool isAReg);
	void CPU_RR(BYTE& reg, bool isAReg);
	void CPU_RR_MEM(WORD address, bool isAReg);
	void CPU_DDFD_RL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DDFD_RR(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_RLD();
	void CPU_RRD();
	void CPU_SLA(BYTE& reg);
	void CPU_SLA_MEM(WORD address);
	void CPU_SRA(BYTE& reg);
	void CPU_SRA_MEM(WORD address);
	void CPU_SRL(BYTE& reg);
	void CPU_SRL_MEM(WORD address);
	void CPU_SLL(BYTE& reg);
	void CPU_SLL_MEM(WORD address);
	void CPU_DDFD_SLA(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DDFD_SRA(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DDFD_SRL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_DDFD_SLL(BYTE& reg, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_RESET_BIT(BYTE& reg, int bit);
	void CPU_DDFD_RESET_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_RESET_BIT_MEM(WORD address, int bit);
	void CPU_TEST_BIT(BYTE reg, int bit, int cycles);
	void CPU_DDFD_TEST_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_SET_BIT(BYTE& reg, int bit);
	void CPU_DDFD_SET_BIT(BYTE& reg, int bit, WORD& ixiyreg, SIGNED_BYTE& displacement);
	void CPU_SET_BIT_MEM(WORD address, int bit);
	void CPU_IN(BYTE& data);
	void CPU_IN_IMMEDIATE(BYTE& data);
	void CPU_OUT(const BYTE& address, const BYTE& data);
	void CPU_OUT_IMMEDIATE(const BYTE& data);
	void CPU_OUTI();
	void CPU_OTIR();
	void CPU_OUTD();
	void CPU_OUTDR();
	void CPU_CPI();
	void CPU_CPIR();
	void CPU_CPD();
	void CPU_CPDR();
	void CPU_INI();
	void CPU_INIR();
	void CPU_IND();
	void CPU_INDR();
	void CPU_LDI();
	void CPU_LDIR();
	void CPU_DJNZ();
	void CPU_LDD();
	void CPU_LDDR();
	void CPU_LDA_I();
	void CPU_LDA_R();
	void CPU_REG_LOAD_NNN(WORD& reg);
	void CPU_EXCHANGE(WORD& reg1, WORD& reg2);
};


#endif // !_Z80_H
