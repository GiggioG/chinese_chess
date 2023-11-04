#pragma once;
#include "SDL.h"
class MenuScreen {
public:
	MenuScreen();
	~MenuScreen();

	SDL_Renderer* m_renderer;
	int m_screenWidth;
	int m_screenHeight;
	SDL_Rect m_playButtonHoverRect;
	bool m_buttonHovered;
	bool m_buttonPressed;
	bool m_proceed = false;

	void init(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	void update();
	void draw();
};