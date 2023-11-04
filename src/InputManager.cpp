#include "InputManager.h"
#include "ConfigManager.h"

Coord InputManager::m_mouseCoords = { 0,0 };
bool InputManager::m_mousePressed = false;

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

void InputManager::handleEvents() {
    m_mousePressed = false;

    SDL_Event m_event;
    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(m_mouseCoords.x), &(m_mouseCoords.y));

            m_mouseCoords.x *= float(1920.0f / 1366.0f);
            m_mouseCoords.y *= float(1080.0f / 768.0f);

            break;
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_mousePressed = true;
            }
            break;
        }
    }
}

bool InputManager::coordInRect(Coord c, SDL_Rect r) {
    int buttonTopLeftX = r.x;
    int buttonTopLeftY = r.y;
    int buttonBottomRightX = r.x + r.w;
    int buttonBottomRightY = r.y + r.h;
    return (m_mouseCoords.x >= buttonTopLeftX && m_mouseCoords.x <= buttonBottomRightX
		&& m_mouseCoords.y >= buttonTopLeftY && m_mouseCoords.y <= buttonBottomRightY);
}