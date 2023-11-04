#include "Pawn.h"
#include "TextureManager.h"

Pawn::Pawn() {

}

Pawn::~Pawn() {

}

void Pawn::init(SDL_Renderer* renderer, TEAMS team, PAWN_ROLES role, Tile* tile) {
	m_renderer = renderer;
	m_team = team;
	m_role = role;
	m_tile = tile;
	if (m_role == PAWN_ROLES::PAWN) {
		if (m_team == TEAMS::RIGHT) {
			m_texture = TextureManager::m_pawnRight;
		} else if (m_team == TEAMS::LEFT) {
			m_texture = TextureManager::m_pawnLeft;
		}
	}else if (m_role == PAWN_ROLES::SENSEI) {
		if (m_team == TEAMS::RIGHT) {
			m_texture = TextureManager::m_senseiRight;
		}else if (m_team == TEAMS::LEFT) {
			m_texture = TextureManager::m_senseiLeft;
		}
	}
}

void Pawn::draw(){
	if (m_selected) {
		SDL_RenderCopy(m_renderer, TextureManager::m_selectedPawn, NULL, m_tile->m_rect);
	}
	SDL_RenderCopy(m_renderer, m_texture, NULL, m_tile->m_rect);
}

void Pawn::move(Tile* tile) {
	m_tile = tile;
}
