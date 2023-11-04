#pragma once
#include <vector>
#include <fstream>
#include <map>
#include "SDL.h"
#include "Coord.h"
#include "CardType.h"
class ConfigManager {
public:
	ConfigManager();
	~ConfigManager();

	static std::vector<CARDTYPES> m_cards;
	static std::map<CARDTYPES, std::vector<Coord>> m_cardMoves;

	static int m_squareSize;
	static SDL_Rect m_Player_1_On_Turn_Rect;
	static SDL_Rect m_Player_2_On_Turn_Rect;
	static std::string m_Player_1_On_Turn_Coin;
	static std::string m_Player_2_On_Turn_Coin;
	static std::string m_selectedPawn;
	static std::string m_selectedCard;
	static Coord m_cardWH;
	static Coord m_leftTopCard;
	static Coord m_leftBottomCard;
	static Coord m_rightTopCard;
	static Coord m_rightBottomCard;
	static Coord m_toLeftCard;
	static Coord m_toRightCard;
	static int m_buttonHoverGrow;

	static std::string m_winScreen_Player1;
	static std::string m_winScreen_Player2;
	static std::string m_winScreenExitButton;
	static SDL_Rect m_winScreenExitButtonRect;
	static std::string m_winScreenPlayButton;
	static SDL_Rect m_winScreenPlayButtonRect;

	static std::string m_menuBackground;
	static std::string m_menuPlayButton;
	static SDL_Rect m_menuPlayButtonRect;

	void init();
	void loadCards();
	void loadGameConfig();
	void loadWinScreenConfig();
	void loadMenuConfig();

private:
	std::fstream stream;
	std::string tmp;
};