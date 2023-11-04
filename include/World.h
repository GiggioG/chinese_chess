#pragma once
#include "SDL.h"
#include "Grid.h"
#include "InputManager.h"
#include "Card.h"
#include "WinScreen.h"
#include "TextureManager.h"
#include "GameState.h"
#include "ConfigManager.h"
#include "MenuScreen.h"

class World {
public:
	World();
	~World();

	bool m_run;
	int m_screenWidth;
	int m_screenHeight;
	SDL_Window* m_mainWindow;
	SDL_Renderer* m_mainRenderer;
	Grid m_grid;
	InputManager m_inputManager;
	TextureManager m_textureManager;
	WinScreen m_winScreen;
	GAME_STATES m_gameState = GAME_STATES::MENU;
	ConfigManager m_configManager;
	MenuScreen m_menuScreen;

	void init();
	void update();
	void draw();
	void exit();
	void initSDL();
	static bool PointInRect(Coord& c, SDL_Rect& r);
};