#include "Config.h"
#include "Emulator.h"
#include "GameBoy.h"

#ifdef WIN32
#include <Windows.h>
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#endif

static const int windowWidth = 160;
static const int windowHeight = 144;

static const char* windowTitle = "GameBoy";
static SDL_Window* window;

///////////////////////////////////////////////////////////////////////////////////////

static int total = 0;
static int timer = 0;
static int current = 0;
static int counter = 0;
static bool first = true;

static void CheckFPS()
{
	if (first)
	{
		first = false;
		timer = SDL_GetTicks();
	}

	counter++;
	current = SDL_GetTicks();
	if ((timer + 1000) < current)
	{
		timer = current;
		total = counter;
		counter = 0;

		//OutputDebugStr(outputMessage);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

static void DoRender()
{
	GameBoy* gb = GameBoy::GetSingleton();
	gb->RenderGame();
}

///////////////////////////////////////////////////////////////////////////////////////

GameBoy* GameBoy::m_Instance = nullptr;

GameBoy* GameBoy::CreateInstance()
{
	if (0 == m_Instance)
	{
		m_Instance = new GameBoy();
		m_Instance->Initialize();
	}
	return m_Instance;
}

//////////////////////////////////////////////////////////////////////////////////////////

GameBoy* GameBoy::GetSingleton()
{
	return m_Instance;
}

//////////////////////////////////////////////////////////////////////////////////////////

GameBoy::GameBoy(void) :
	m_Emulator(nullptr)
{
	m_Emulator = new Emulator();
	m_Emulator->LoadRom("ROMS/Tetris.gb");
	m_Emulator->InitGame(DoRender);
}

//////////////////////////////////////////////////////////////////////////////////////////

bool GameBoy::Initialize()
{
	return CreateSDLWindow();
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameBoy::StartEmulation()
{
	bool quit = false;
	SDL_Event event;

	float fps = 59.73;
	float interval = 1000;
	interval /= fps;

	unsigned int time2 = SDL_GetTicks();

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			HandleInput(event);

			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		unsigned int current = SDL_GetTicks();

		if ((time2 + interval) < current)
		{
			CheckFPS();
			m_Emulator->Update();
			time2 = current;
		}

	}
	SDL_Quit();
}

//////////////////////////////////////////////////////////////////////////////////////////

GameBoy::~GameBoy(void)
{
	delete m_Emulator;
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameBoy::RenderGame()
{
	//EmulationLoop();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRasterPos2i(-1, 1);
	glPixelZoom(1, -1);
	glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, m_Emulator->m_ScreenData);

	//SDL_GL_SwapBuffers( );
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */

	//SDL_GL_SetSwapInterval(1);

	/* Swap our buffer to display the current contents of buffer on screen */
	SDL_GL_SwapWindow(window);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameBoy::SetKeyPressed(int key)
{
	m_Emulator->KeyPressed(key);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameBoy::SetKeyReleased(int key)
{
	m_Emulator->KeyReleased(key);
}

//////////////////////////////////////////////////////////////////////////////////////////

bool GameBoy::CreateSDLWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == nullptr)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return true;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	InitGL();

	//SDL_GL_DeleteContext(glcontext);

	// Close and destroy the window
	//SDL_DestroyWindow(window);

	// Clean up
	//SDL_Quit();

	//SDL_WM_SetCaption( "OpenGL Test", NULL );
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameBoy::InitGL()
{
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, windowWidth, windowHeight, 0, -1.0, 1.0);
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameBoy::HandleInput(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		int key = -1;
		switch (event.key.keysym.sym)
		{
		case SDLK_a: key = 4; break;
		case SDLK_s: key = 5; break;
		case SDLK_RETURN: key = 7; break;
		case SDLK_SPACE: key = 6; break;
		case SDLK_RIGHT: key = 0; break;
		case SDLK_LEFT: key = 1; break;
		case SDLK_UP: key = 2; break;
		case SDLK_DOWN: key = 3; break;
		}
		if (key != -1)
		{
			SetKeyPressed(key);
		}
	}
	//If a key was released
	else if (event.type == SDL_KEYUP)
	{
		int key = -1;
		switch (event.key.keysym.sym)
		{
		case SDLK_a: key = 4; break;
		case SDLK_s: key = 5; break;
		case SDLK_RETURN: key = 7; break;
		case SDLK_SPACE: key = 6; break;
		case SDLK_RIGHT: key = 0; break;
		case SDLK_LEFT: key = 1; break;
		case SDLK_UP: key = 2; break;
		case SDLK_DOWN: key = 3; break;
		}
		if (key != -1)
		{
			SetKeyReleased(key);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
