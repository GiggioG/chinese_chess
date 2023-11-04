#pragma once
#include <vector>
#include "SDL.h"
#include "Coord.h"
#include "CardType.h"
#include "Team.h"
class Card {
public:
	Card();
	~Card();

	std::vector<Coord> m_offsets; // for the left player
	CARDTYPES m_type;
	TEAMS m_team;
	SDL_Texture* m_texture;
	SDL_Texture* m_textureReversed;
	SDL_Rect m_rect;

	void init(CARDTYPES type, TEAMS team, SDL_Rect rect);
	void addOffset(int roff, int coff);
	SDL_Texture* getTexture();
};