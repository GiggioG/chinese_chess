#pragma once;
#include "SDL.h"
#include "Team.h"
class WinScreen {
public:
	WinScreen();
	~WinScreen();

	SDL_Renderer* m_renderer;
	int m_screenWidth;
	int m_screenHeight;
	TEAMS m_winner = TEAMS::NONE;
	bool m_proceed = false;
	bool m_playAgain = false;
	bool m_exitButtonHovered = false;
	bool m_exitButtonPressed = false;
	SDL_Rect m_exitButtonHoverRect;
	bool m_playButtonHovered = false;
	bool m_playButtonPressed = false;
	SDL_Rect m_playButtonHoverRect;

	void init(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	void update();
	void draw();
};