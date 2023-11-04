#pragma once
#include "SDL.h"
#include "Team.h"
#include "PawnRole.h"
#include "Tile.h"
class Pawn {
public:
	Pawn();
	~Pawn();

	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	TEAMS m_team;
	PAWN_ROLES m_role;
	Tile* m_tile;
	bool m_selected = false;

	void init(SDL_Renderer* renderer, TEAMS team, PAWN_ROLES role, Tile* tile);
	void draw();
	void move(Tile* tile);
};