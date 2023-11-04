#pragma once
#include "Coord.h"
#include "SDL.h"
class InputManager {
public:
	InputManager();
	~InputManager();

	static Coord m_mouseCoords;
	static bool m_mousePressed;

	void handleEvents();
	static bool coordInRect(Coord c, SDL_Rect r);
};