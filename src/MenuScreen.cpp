#include <iostream>
#include "MenuScreen.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "ConfigManager.h"
MenuScreen::MenuScreen() {

}
MenuScreen::~MenuScreen(){

}

void MenuScreen::init(SDL_Renderer* renderer, int screenWidth, int screenHeight){
	m_renderer = renderer;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_playButtonHoverRect.x = ConfigManager::m_menuPlayButtonRect.x - ConfigManager::m_buttonHoverGrow;
	m_playButtonHoverRect.y = ConfigManager::m_menuPlayButtonRect.y - ConfigManager::m_buttonHoverGrow;
	m_playButtonHoverRect.w = ConfigManager::m_menuPlayButtonRect.w + ConfigManager::m_buttonHoverGrow * 2;
	m_playButtonHoverRect.h = ConfigManager::m_menuPlayButtonRect.h + ConfigManager::m_buttonHoverGrow * 2;
}

void MenuScreen::update() {
	m_buttonHovered = InputManager::coordInRect(InputManager::m_mouseCoords, ConfigManager::m_menuPlayButtonRect);
	m_buttonPressed = m_buttonHovered && InputManager::m_mousePressed;
	if (m_buttonPressed) {
		m_proceed = true;
	}
}

void MenuScreen::draw() {
	SDL_RenderCopy(m_renderer, TextureManager::m_menuBackground, NULL, NULL);
	if (m_buttonHovered) {
		SDL_RenderCopy(m_renderer, TextureManager::m_menuPlayButton, NULL, &m_playButtonHoverRect);
	} else {
		SDL_RenderCopy(m_renderer, TextureManager::m_menuPlayButton, NULL, &ConfigManager::m_menuPlayButtonRect);
	}
}
