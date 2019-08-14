#pragma once
#ifndef _GAMEBOY_H
#define _GAMEBOY_H

class Emulator;

#include "Emulator.h"
#ifdef WIN32
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

class GameBoy
{
public:
	static				GameBoy* CreateInstance();
	static				GameBoy* GetSingleton();

	~GameBoy(void);

	void					RenderGame() const;
	bool					Initialize();
	void					SetKeyPressed(int key) const;
	void					SetKeyReleased(int key) const;
	void					StartEmulation() const;
	void					HandleInput(SDL_Event& event) const;
private:
	GameBoy(void);

	bool					CreateSDLWindow();

	void					InitGL();

	static				GameBoy* m_Instance;

	Emulator* m_Emulator;
};

#endif
