#include <iostream>
#include "World.h"

World::World(){
}

World::~World(){
}

void World::init(){
	m_configManager.init();
	m_screenWidth = 1920;
	m_screenHeight = 1080;
	initSDL();
	m_winScreen.init(m_mainRenderer, m_screenHeight, m_screenHeight);
	m_menuScreen.init(m_mainRenderer, m_screenHeight, m_screenHeight);
	{//improveRender();
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);

		auto desktopWidth = DM.w;
		auto desktopHeight = DM.h;

		if (SDL_SetWindowFullscreen(m_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		{
			std::cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << '\n';
		}

		SDL_RenderSetLogicalSize(m_mainRenderer, m_screenWidth, m_screenHeight);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	}

	m_grid.init(m_mainRenderer, m_screenWidth, m_screenHeight);

	m_run = true;
}

void World::update(){
	m_inputManager.handleEvents();
	if (m_gameState == GAME_STATES::MENU) { 
		m_menuScreen.update();
		if (m_menuScreen.m_proceed) {
			m_gameState = GAME_STATES::PLAYING;
		}
	} else if (m_gameState == GAME_STATES::PLAYING) {
		m_grid.update();
		if (m_grid.m_winner != TEAMS::NONE) {
			m_gameState = GAME_STATES::WINSCREEN;
			m_winScreen.m_winner = m_grid.m_winner;
		}
	} else if (m_gameState == GAME_STATES::WINSCREEN) {
		m_winScreen.update();
		if (m_winScreen.m_proceed) {
			m_run = false;
		}
	}
}

void World::draw(){
	if (m_gameState == GAME_STATES::MENU) {
		m_menuScreen.draw();
	} else if (m_gameState == GAME_STATES::PLAYING) {
		SDL_RenderCopy(m_mainRenderer, TextureManager::m_background, NULL, NULL);
		m_grid.draw();
	} else if (m_gameState == GAME_STATES::WINSCREEN) {
		m_winScreen.draw();
	}
	SDL_RenderPresent(m_mainRenderer);
}

void World::exit(){
}

void World::initSDL(){
	m_mainWindow = SDL_CreateWindow("Chinese Chess",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, 0);
	//SDL_SetWindowFullscreen(m_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

	m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	m_textureManager.init(m_mainRenderer);
}

bool World::PointInRect(Coord& c, SDL_Rect& r) {
	if (c.x < r.x) { return false; }
	if (c.y < r.y) { return false; }
	if (c.x > r.x + r.w) { return false; }
	if (c.y > r.y + r.h) { return false; }
	return true;
}