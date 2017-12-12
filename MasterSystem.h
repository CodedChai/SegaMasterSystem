#pragma once
#ifndef _MASTER_SYSTEM_H
#define _MASTER_SYSTEM_H

class Emulator;

#include <Windows.h>
#include "SDL.h"
#include "SDL_opengl.h"


class MasterSystem
{
public:
	static MasterSystem* CreateInstance();

	bool CreateSDLWindow();
	void StartRom(const char* path);
	void BeginGame(int fps, bool useGfxOpt);
	unsigned char GetMemoryByte(int i);

	~MasterSystem(void);

private:
	MasterSystem(void);

	void InitGL();
	void RenderGame();
	void RomLoop(int fps);
	void HandleInput(const SDL_Event& event);

	static	MasterSystem* m_Instance;
	Emulator* m_Emulator;
	int	m_Width;
	int	m_Height;
	bool m_UseGFXOpt;
};

#endif

