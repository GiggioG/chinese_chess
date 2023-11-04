#include <iostream>
#include "ConfigManager.h"


std::vector<std::string> ConfigManager::m_cards = {};
std::map<std::string, std::vector<Coord>> ConfigManager::m_cardMoves = {};

int ConfigManager::m_squareSize = -1;
SDL_Rect ConfigManager::m_Player_1_On_Turn_Rect = {-1, -1, -1, -1};
SDL_Rect ConfigManager::m_Player_2_On_Turn_Rect = {-1, -1, -1, -1};
std::string ConfigManager::m_Player_1_On_Turn_Coin = "";
std::string ConfigManager::m_Player_2_On_Turn_Coin = "";
std::string ConfigManager::m_selectedPawn = "";
std::string ConfigManager::m_selectedCard = "";
Coord ConfigManager::m_cardWH = { -1, -1 };
Coord ConfigManager::m_leftTopCard = { -1, -1 };
Coord ConfigManager::m_leftBottomCard = { -1, -1 };
Coord ConfigManager::m_rightTopCard = { -1, -1 };
Coord ConfigManager::m_rightBottomCard = { -1, -1 };
Coord ConfigManager::m_toLeftCard = { -1, -1 };
Coord ConfigManager::m_toRightCard = { -1, -1 };
int ConfigManager::m_buttonHoverGrow = -1;

std::string ConfigManager::m_winScreen_Player1 = "";
std::string ConfigManager::m_winScreen_Player2 = "";
std::string ConfigManager::m_winScreenExitButton = "";
SDL_Rect ConfigManager::m_winScreenExitButtonRect = {-1, -1, -1, -1};
std::string ConfigManager::m_winScreenPlayButton = "";
SDL_Rect ConfigManager::m_winScreenPlayButtonRect = { -1, -1, -1, -1 };


std::string ConfigManager::m_menuBackground = "";
std::string ConfigManager::m_menuPlayButton = "";
SDL_Rect ConfigManager::m_menuPlayButtonRect = {-1, -1, -1, -1};


ConfigManager::ConfigManager() {

}
ConfigManager::~ConfigManager() {

}

void ConfigManager::init() {
    loadCards();
    loadGameConfig();
    loadWinScreenConfig();
    loadMenuConfig();
}

void ConfigManager::loadCards() {
    bool readingCard = false;
    bool cOffset = false; // false: rows, true: cols
    CARDTYPES currentCard;
    std::vector<Coord> moves;
    Coord move;
    stream.open("config\\cards.txt");
    while (!stream.eof()) {
        stream >> tmp;
        if (!readingCard) {
            currentCard = tmp;
            readingCard = true;
        }
        else {
            if (tmp == ";") {
                m_cardMoves[currentCard] = moves;
                m_cards.push_back(currentCard);
                moves.clear();
                readingCard = false;
                continue;
            }
            if (!cOffset) {
                move.y = stoi(tmp);
            }
            else {
                move.x = stoi(tmp);
                moves.push_back(move);
            }
            cOffset = !cOffset;
        }
    }
    stream.close();
}

void ConfigManager::loadGameConfig() {
    stream.open("config\\game.txt");
    std::string trash;
    {
        stream >> trash;
        stream >> m_squareSize;

        stream >> trash;
        stream >> m_Player_1_On_Turn_Rect.x;
        stream >> m_Player_1_On_Turn_Rect.y;
        stream >> m_Player_1_On_Turn_Rect.w;
        stream >> m_Player_1_On_Turn_Rect.h;

        stream >> trash;
        stream >> m_Player_2_On_Turn_Rect.x;
        stream >> m_Player_2_On_Turn_Rect.y;
        stream >> m_Player_2_On_Turn_Rect.w;
        stream >> m_Player_2_On_Turn_Rect.h;

        stream >> trash;
        stream >> m_Player_1_On_Turn_Coin;

        stream >> trash;
        stream >> m_Player_2_On_Turn_Coin;

        stream >> trash;
        stream >> m_selectedPawn;
        
        stream >> trash;
        stream >> m_selectedCard;

        stream >> trash;
        stream >> m_cardWH.x;
        stream >> m_cardWH.y;

        stream >> trash;
        stream >> m_leftTopCard.x;
        stream >> m_leftTopCard.y;

        stream >> trash;
        stream >> m_leftBottomCard.x;
        stream >> m_leftBottomCard.y;

        stream >> trash;
        stream >> m_rightTopCard.x;
        stream >> m_rightTopCard.y;

        stream >> trash;
        stream >> m_rightBottomCard.x;
        stream >> m_rightBottomCard.y;

        stream >> trash;
        stream >> m_toLeftCard.x;
        stream >> m_toLeftCard.y;

        stream >> trash;
        stream >> m_toRightCard.x;
        stream >> m_toRightCard.y;

        stream >> trash;
        stream >> m_buttonHoverGrow;
    }
    /*
		m_squareSize            int
		m_Player_1_On_Turn_Rect   rect
		m_Player_2_On_Turn_Rect   rect
		m_Player_1_On_Turn_Coin   string
		m_Player_2_On_Turn_Coin   string
		m_selectedPawn            string
		m_selectedCard              string
		m_cardWH                  coord
		m_leftTopCard             coord
		m_leftBottomCard          coord
		m_rightTopCard            coord
		m_rightBottomCard         coord
		m_toLeftCard              coord
		m_toRightCard              coord
	};
    */
    stream.close();
}

void ConfigManager::loadWinScreenConfig() {
    stream.open("config\\winScreen.txt");
    std::string trash;
    {
        stream >> trash;
        stream >> m_winScreen_Player1;

        stream >> trash;
        stream >> m_winScreen_Player2;

        stream >> trash;
        stream >> m_winScreenExitButton;

        stream >> trash;
        stream >> m_winScreenExitButtonRect.x;
        stream >> m_winScreenExitButtonRect.y;
        stream >> m_winScreenExitButtonRect.w;
        stream >> m_winScreenExitButtonRect.h;

        stream >> trash;
        stream >> m_winScreenPlayButton;

        stream >> trash;
        stream >> m_winScreenPlayButtonRect.x;
        stream >> m_winScreenPlayButtonRect.y;
        stream >> m_winScreenPlayButtonRect.w;
        stream >> m_winScreenPlayButtonRect.h;
    }
    stream.close();
}

void ConfigManager::loadMenuConfig() {
    stream.open("config\\menu.txt");
    std::string trash;
    {
        stream >> trash;
        stream >> m_menuBackground;

        stream >> trash;
        stream >> m_menuPlayButton;

        stream >> trash;
        stream >> m_menuPlayButtonRect.x;
        stream >> m_menuPlayButtonRect.y;
        stream >> m_menuPlayButtonRect.w;
        stream >> m_menuPlayButtonRect.h;
    }
    stream.close();
}