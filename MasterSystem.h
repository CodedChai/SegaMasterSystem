#pragma once
#ifndef _MASTER_SYSTEM_H
#define _MASTER_SYSTEM_H

class Emulator;

#ifdef WIN32
#include <Windows.h>
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#endif

class MasterSystem
{
public:
	static MasterSystem* CreateInstance();

	bool CreateSDLWindow();
	void StartROM(const char* path);
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

