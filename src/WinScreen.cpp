#include <iostream>
#include "WinScreen.h"
#include "TextureManager.h"
#include "ConfigManager.h"
#include "InputManager.h"
WinScreen::WinScreen() {

}
WinScreen::~WinScreen(){

}

void WinScreen::init(SDL_Renderer* renderer, int screenWidth, int screenHeight){
	m_renderer = renderer;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_exitButtonHoverRect.x = ConfigManager::m_winScreenExitButtonRect.x - ConfigManager::m_buttonHoverGrow;
	m_exitButtonHoverRect.y = ConfigManager::m_winScreenExitButtonRect.y - ConfigManager::m_buttonHoverGrow;
	m_exitButtonHoverRect.w = ConfigManager::m_winScreenExitButtonRect.w + ConfigManager::m_buttonHoverGrow * 2;
	m_exitButtonHoverRect.h = ConfigManager::m_winScreenExitButtonRect.h + ConfigManager::m_buttonHoverGrow * 2;

	m_playButtonHoverRect.x = ConfigManager::m_winScreenPlayButtonRect.x - ConfigManager::m_buttonHoverGrow;
	m_playButtonHoverRect.y = ConfigManager::m_winScreenPlayButtonRect.y - ConfigManager::m_buttonHoverGrow;
	m_playButtonHoverRect.w = ConfigManager::m_winScreenPlayButtonRect.w + ConfigManager::m_buttonHoverGrow * 2;
	m_playButtonHoverRect.h = ConfigManager::m_winScreenPlayButtonRect.h + ConfigManager::m_buttonHoverGrow * 2;
}

void WinScreen::update() {
	m_exitButtonHovered = InputManager::coordInRect(InputManager::m_mouseCoords, ConfigManager::m_winScreenExitButtonRect);
	m_exitButtonPressed = m_exitButtonHovered && InputManager::m_mousePressed;

	m_playButtonHovered = InputManager::coordInRect(InputManager::m_mouseCoords, ConfigManager::m_winScreenPlayButtonRect);
	m_playButtonPressed = m_playButtonHovered && InputManager::m_mousePressed;

	if (m_playButtonPressed) {
		m_playAgain = true;
		m_proceed = true;
	}

	if (m_exitButtonPressed) {
		m_proceed = true;
	}
}

void WinScreen::draw() {
	if (m_winner == TEAMS::LEFT) {
		SDL_RenderCopy(m_renderer, TextureManager::m_leftWon, NULL, NULL);
	} else if (m_winner == TEAMS::RIGHT) {
		SDL_RenderCopy(m_renderer, TextureManager::m_rightWon, NULL, NULL);
	}

	if (m_exitButtonHovered) {
		SDL_RenderCopy(m_renderer, TextureManager::m_winScreenExitButton, NULL, &m_exitButtonHoverRect);
	} else {
		SDL_RenderCopy(m_renderer, TextureManager::m_winScreenExitButton, NULL, &ConfigManager::m_winScreenExitButtonRect);
	}

	if (m_playButtonHovered) {
		SDL_RenderCopy(m_renderer, TextureManager::m_winScreenPlayButton, NULL, &m_playButtonHoverRect);
	} else {
		SDL_RenderCopy(m_renderer, TextureManager::m_winScreenPlayButton, NULL, &ConfigManager::m_winScreenPlayButtonRect);
	}

	/*{
		SDL_Rect rect;
		rect.x = 700;
		rect.y = 40;
		rect.w = 120;
		rect.h = 120;
		for (int i = 0; i < 6; i++) {
			SDL_RenderCopy(m_renderer, TextureManager::m_menuBackground, NULL, &rect);
			rect.y += rect.h;
		}
		for (int i = 0; i < 4; i++) {
			SDL_RenderCopy(m_renderer, TextureManager::m_menuBackground, NULL, &rect);
			rect.x += rect.w;
		}
	}*/
}
