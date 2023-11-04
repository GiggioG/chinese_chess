#pragma once
#include "SDL.h"
class Tile {
public:
	Tile();
	~Tile();

	SDL_Renderer* m_renderer;
	SDL_Rect* m_rect;
	SDL_Texture* m_texture;
	bool m_hover = false;

	void init(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);
	void draw();
};