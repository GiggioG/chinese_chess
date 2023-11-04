#include "Tile.h"
#include "TextureManager.h"
#include "ConfigManager.h"

Tile::Tile() {

}
Tile::~Tile() {

}

void Tile::init(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture){
	m_renderer = renderer;
	m_rect = new SDL_Rect{x, y, ConfigManager::m_squareSize, ConfigManager::m_squareSize };
	m_texture = texture;
}

void Tile::draw() {
	//SDL_RenderCopy(m_renderer, m_texture, NULL, m_rect);
	if (m_hover) {
		SDL_RenderCopy(m_renderer, TextureManager::m_hover, NULL, m_rect);
		m_hover = false;
	}
}