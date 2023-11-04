#pragma once
#include <string>
#include "SDL.h"
class TextureManager {
public:
	TextureManager();
	~TextureManager();

	static SDL_Surface* m_loadingSurface;
	static SDL_Renderer* m_renderer;

	static SDL_Texture* m_background;
	static SDL_Texture* m_emptyTile;
	static SDL_Texture* m_hover;
	static SDL_Texture* m_pawnLeft;
	static SDL_Texture* m_pawnRight;
	static SDL_Texture* m_senseiLeft;
	static SDL_Texture* m_senseiRight;
	static SDL_Texture* m_selectedPawn;
	static SDL_Texture* m_selectedCard;
	static SDL_Texture* m_allowedTile;
	static SDL_Texture* m_leftWon;
	static SDL_Texture* m_rightWon;
	static SDL_Texture* m_leftTurnCoin;
	static SDL_Texture* m_rightTurnCoin;
	static SDL_Texture* m_menuBackground;
	static SDL_Texture* m_menuPlayButton;
	static SDL_Texture* m_winScreenExitButton;
	static SDL_Texture* m_winScreenPlayButton;

	void init(SDL_Renderer* renderer);
	static SDL_Texture* loadTexture(std::string filename);
};