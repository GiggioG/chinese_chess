#include "Card.h"
#include "TextureManager.h"
#include "ConfigManager.h"

Card::Card() {
}

Card::~Card() {
}

void Card::addOffset(int roff, int coff) {
	m_offsets.push_back({ coff, roff });
}

void Card::init(CARDTYPES type, TEAMS team, SDL_Rect rect){
	m_type = type;
	m_team = team;
	m_rect = rect;
	m_texture = TextureManager::loadTexture("img\\CARDS\\" + type + ".bmp");
	m_textureReversed = TextureManager::loadTexture("img\\CARDS\\" + type + "_reversed.bmp");
	m_offsets = ConfigManager::m_cardMoves[type];
}

SDL_Texture* Card::getTexture() {
	if (m_team == TEAMS::LEFT) {
		return m_texture;
	}
	else if (m_team == TEAMS::RIGHT) {
		return m_textureReversed;
	}
}