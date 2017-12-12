#pragma once
#ifndef _SMS_EMULATOR_H
#define _SMS_EMULATOR_H

#include "Z80.h"

class Emulator {
public:
	static Emulator* CreateInstance();
	static Emulator* GetSingleton();
	~Emulator(void);

private:
	static Emulator* m_Instance;
	Emulator(void);
};


#endif // !_SMS_EMULATOR_H
