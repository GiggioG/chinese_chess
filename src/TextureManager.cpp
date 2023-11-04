#include "TextureManager.h"
#include "ConfigManager.h"
#include <iostream>

SDL_Surface* TextureManager::m_loadingSurface = nullptr;
SDL_Renderer* TextureManager::m_renderer = nullptr;

SDL_Texture* TextureManager::m_background = nullptr;
SDL_Texture* TextureManager::m_emptyTile = nullptr;
SDL_Texture* TextureManager::m_hover = nullptr;
SDL_Texture* TextureManager::m_pawnLeft = nullptr;
SDL_Texture* TextureManager::m_pawnRight = nullptr;
SDL_Texture* TextureManager::m_senseiLeft = nullptr;
SDL_Texture* TextureManager::m_senseiRight = nullptr;
SDL_Texture* TextureManager::m_selectedPawn = nullptr;
SDL_Texture* TextureManager::m_selectedCard = nullptr;
SDL_Texture* TextureManager::m_allowedTile = nullptr;
SDL_Texture* TextureManager::m_leftWon = nullptr;
SDL_Texture* TextureManager::m_rightWon = nullptr;
SDL_Texture* TextureManager::m_leftTurnCoin = nullptr;
SDL_Texture* TextureManager::m_rightTurnCoin = nullptr;
SDL_Texture* TextureManager::m_menuBackground = nullptr;
SDL_Texture* TextureManager::m_menuPlayButton = nullptr;
SDL_Texture* TextureManager::m_winScreenExitButton = nullptr;
SDL_Texture* TextureManager::m_winScreenPlayButton = nullptr;

TextureManager::TextureManager() {

}
TextureManager::~TextureManager() {

}

void TextureManager::init(SDL_Renderer* renderer) {
	m_renderer = renderer;

	m_background = loadTexture("img\\game\\background.bmp");

	m_emptyTile = loadTexture("img\\game\\unused.bmp");

	m_hover = loadTexture("img\\game\\hover.bmp");

	m_pawnLeft = loadTexture("img\\pawns\\pawn1.bmp");

	m_pawnRight = loadTexture("img\\pawns\\pawn2.bmp");

	m_senseiLeft = loadTexture("img\\pawns\\senseiPawn1.bmp");

	m_senseiRight = loadTexture("img\\pawns\\senseiPawn2.bmp");

	m_selectedPawn = loadTexture(ConfigManager::m_selectedPawn);

	m_selectedCard = loadTexture(ConfigManager::m_selectedCard);

	m_allowedTile = loadTexture("img\\game\\gridPossMove.bmp");

	m_leftWon = loadTexture(ConfigManager::m_winScreen_Player1);

	m_rightWon = loadTexture(ConfigManager::m_winScreen_Player2);

	m_leftTurnCoin = loadTexture(ConfigManager::m_Player_1_On_Turn_Coin);

	m_rightTurnCoin = loadTexture(ConfigManager::m_Player_2_On_Turn_Coin);

	m_menuBackground = loadTexture(ConfigManager::m_menuBackground);
	
	m_menuPlayButton = loadTexture(ConfigManager::m_menuPlayButton);

	m_winScreenExitButton = loadTexture(ConfigManager::m_winScreenExitButton);

	m_winScreenPlayButton = loadTexture(ConfigManager::m_winScreenPlayButton);
}

SDL_Texture* TextureManager::loadTexture(std::string filename) {
	SDL_Texture* to_return;
	m_loadingSurface = SDL_LoadBMP(filename.c_str());
	to_return = SDL_CreateTextureFromSurface(m_renderer, m_loadingSurface);
	SDL_FreeSurface(m_loadingSurface);
	return to_return;
}