#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include "Debug.h"
#include "Grid.h"
#include "Tile.h"
#include "SDL.h"
#include "World.h"
#include "TextureManager.h"

Grid::Grid(){

}

Grid::~Grid() {

}

void Grid::init(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
	m_renderer = renderer;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//init card rects
	m_leftTopCardRect = { ConfigManager::m_leftTopCard.x, ConfigManager::m_leftTopCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };
	m_leftBottomCardRect = { ConfigManager::m_leftBottomCard.x, ConfigManager::m_leftBottomCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };
	m_rightTopCardRect = { ConfigManager::m_rightTopCard.x, ConfigManager::m_rightTopCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };
	m_rightBottomCardRect = { ConfigManager::m_rightBottomCard.x, ConfigManager::m_rightBottomCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };
	m_toLeftCardRect = { ConfigManager::m_toLeftCard.x, ConfigManager::m_toLeftCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };
	m_toRightCardRect = { ConfigManager::m_toRightCard.x, ConfigManager::m_toRightCard.y, ConfigManager::m_cardWH.x, ConfigManager::m_cardWH.y };

	//init tiles
	m_tiles = new Tile* [5];
	for (int i = 0; i < 5; i++) {
		m_tiles[i] = new Tile[5];
	}

	int x = (m_screenWidth / 2 - ConfigManager::m_squareSize / 2) - 2 * ConfigManager::m_squareSize;
	int y = (m_screenHeight / 2 - ConfigManager::m_squareSize / 2) - 2 * ConfigManager::m_squareSize;
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			m_tiles[r][c].init(m_renderer, x + c * ConfigManager::m_squareSize, y + r * ConfigManager::m_squareSize, TextureManager::m_emptyTile);
		}
	}

	//init pawns
	Pawn* curr_pawn;
	for (int r = 0; r < 5; r++) {
		PAWN_ROLES role = PAWN_ROLES::PAWN;
		if (r == 2) { 
			role = PAWN_ROLES::SENSEI;
		}

		curr_pawn = new Pawn;
		curr_pawn->init(m_renderer, TEAMS::LEFT, role, &m_tiles[r][0]);
		m_pawns.push_back(curr_pawn);

		curr_pawn = new Pawn;
		curr_pawn->init(m_renderer, TEAMS::RIGHT, role, &m_tiles[r][4]);
		m_pawns.push_back(curr_pawn);
	}

	//init cards
	m_leftTopCard = new Card;
	m_leftBottomCard = new Card;
	m_rightTopCard = new Card;
	m_rightBottomCard = new Card;
	m_toLeftCard = new Card;

	std::vector<CARDTYPES> cards = chooseRandomCards(5);
	for (int i = 0; i < 5; i++) {
		std::cout << cards[i] << '\n';
	}

	m_leftTopCard->init(cards[0], TEAMS::LEFT, m_leftTopCardRect);
	m_leftBottomCard->init(cards[1], TEAMS::LEFT, m_leftBottomCardRect);
	m_rightTopCard->init(cards[2], TEAMS::RIGHT, m_rightTopCardRect);
	m_rightBottomCard->init(cards[3], TEAMS::RIGHT, m_rightBottomCardRect);
	m_toLeftCard->init(cards[4], TEAMS::LEFT, m_toLeftCardRect);
}

void Grid::generateAllowed(Coord curr, Card* card, TEAMS team){
	m_allowedTiles.clear();
	int flipFactor = (team == TEAMS::RIGHT ? -1 : 1);
	Coord actual;
	for (Coord& off : card->m_offsets) {
		actual.x = curr.x + off.x * flipFactor;
		actual.y = curr.y + off.y;
		if (actual.x >= 0 && actual.x < 5
		 && actual.y >= 0 && actual.y < 5) {
			m_allowedTiles.push_back(&m_tiles[actual.y][actual.x]);
		}
	}
	//delete from this team
	for (Pawn*& p : m_pawns) {
		if (p->m_team == team) {
			for (int i = m_allowedTiles.size()-1; i >= 0; i--) {
				if (p->m_tile == m_allowedTiles[i]) {
					m_allowedTiles.erase(m_allowedTiles.begin() + i);
				}
			}
		}
	}
}

void Grid::nextTurn(){
	if (m_turn == TEAMS::LEFT) {
		m_toRightCard = *m_selectedCardSlot;
		m_toRightCard->m_rect = m_toRightCardRect;
		m_toRightCard->m_team = nextTeam(m_turn);

		*m_selectedCardSlot = m_toLeftCard;
		m_toLeftCard = nullptr;
		(*m_selectedCardSlot)->m_rect = *m_selectedCardSlotRect;
	} else if (m_turn == TEAMS::RIGHT) {
		m_toLeftCard = *m_selectedCardSlot;
		m_toLeftCard->m_rect = m_toLeftCardRect;
		m_toLeftCard->m_team = nextTeam(m_turn);

		*m_selectedCardSlot = m_toRightCard;
		m_toRightCard = nullptr;
		(*m_selectedCardSlot)->m_rect = *m_selectedCardSlotRect;
	}
	m_selectedCard = nullptr;
	m_turn = nextTeam(m_turn);
}


void Grid::update() {
	int topLeftX = (m_screenWidth / 2 - ConfigManager::m_squareSize / 2) - 2 * ConfigManager::m_squareSize;
	int topLeftY = (m_screenHeight / 2 - ConfigManager::m_squareSize / 2) - 2 * ConfigManager::m_squareSize;
	int bottomRightX = (m_screenWidth / 2 - ConfigManager::m_squareSize / 2) + 3 * ConfigManager::m_squareSize;
	int bottomRightY = (m_screenHeight / 2 - ConfigManager::m_squareSize / 2) + 3 * ConfigManager::m_squareSize;
	if (InputManager::m_mouseCoords.x >= topLeftX && InputManager::m_mouseCoords.x <= bottomRightX
		&& InputManager::m_mouseCoords.y >= topLeftY && InputManager::m_mouseCoords.y <= bottomRightY) {
		int row = (InputManager::m_mouseCoords.y - topLeftY) / ConfigManager::m_squareSize;
		int col = (InputManager::m_mouseCoords.x - topLeftX) / ConfigManager::m_squareSize;
		m_tiles[row][col].m_hover = true;
		if (InputManager::m_mousePressed) {
			bool allowed = false;
			for (auto t : m_allowedTiles) {
				if (&m_tiles[row][col] == t) { allowed = true; }
			}
			/*
			*   pawns: a, b ...
			*   tiles: null (unallowed), alw (allowed)
			*
			*	prev | clicked | selected | consequence
			*	-----+---------+----------+------------
			*	null | null    | null	  |
			*	a    | null    | null     | move a
			*	null | a       | a        |
			*	a    | b       | b        |
			*	a    | a       | null     |
			*/

			Pawn* pawn = nullptr;
			int pawn_idx = -1;
			for (int i = 0; i < m_pawns.size(); i++) {
				if (m_pawns[i]->m_tile == &m_tiles[row][col]) {
					pawn = m_pawns[i];
					pawn_idx = i;
				}
			}
			if (pawn != nullptr) {
				if (m_selectedPawn == nullptr) {
					if (pawn->m_team == m_turn && m_selectedCard != nullptr) {
						m_selectedPawn = pawn;
						m_selectedPawn->m_selected = true;
						if (m_selectedCard != nullptr) {
							generateAllowed({ col, row }, m_selectedCard, m_selectedPawn->m_team);
						}
					}
				} else {
					if (m_selectedPawn == pawn) {
						m_selectedPawn->m_selected = false;
						m_selectedPawn = nullptr;
						m_allowedTiles.clear();
					}else {
						// try capture
						if(allowed && (pawn->m_team != m_selectedPawn->m_team)){
							delete pawn;
							m_pawns.erase(m_pawns.begin() + pawn_idx);
							m_selectedPawn->move(&m_tiles[row][col]);
							m_selectedPawn->m_selected = false;
							m_selectedPawn = nullptr;
							m_allowedTiles.clear();
							nextTurn();
						}
					}
				}
			} else {
				if (m_selectedPawn != nullptr) {
					// try move
					if (allowed) {
						m_selectedPawn->move(&m_tiles[row][col]);
						m_selectedPawn->m_selected = false;
						m_selectedPawn = nullptr;
						m_allowedTiles.clear();
						nextTurn();
					}
				}
			}

			/* old code:
			bool clickedTileEmpty = true;
			for (auto& p : m_pawns) {// Pawn* p
				if (p->m_tile == &m_tiles[row][col]) {
					if (m_selectedPawn == nullptr) {
						m_selectedPawn = p;
						m_selectedPawn->m_selected = true;
					} else {
						if (m_selectedPawn == p) {
							m_selectedPawn->m_selected = false;
							m_selectedPawn = nullptr;
						}else {
							m_selectedPawn->m_selected = false;
							m_selectedPawn = p;
							m_selectedPawn->m_selected = true;
						}
					}
					clickedTileEmpty = false;
					break;
				}
			}
			if (clickedTileEmpty) {
				if (m_selectedPawn != nullptr) {
					m_selectedPawn->move(&m_tiles[row][col]);
					m_selectedPawn->m_selected = false;
				}
				m_selectedPawn = nullptr;
			}
			*/
		}
	} else {
		if (InputManager::m_mousePressed) {
			Coord mouse = InputManager::m_mouseCoords;
			Card* card = nullptr;
			Card** slot = nullptr;
			SDL_Rect* slotRect = nullptr;
			if (m_selectedPawn != nullptr) {
				m_selectedPawn->m_selected = false;
				m_selectedPawn = nullptr;
			}
			if (m_turn == TEAMS::LEFT) {
				if (World::PointInRect(mouse, m_leftTopCardRect))    { 
					card = m_leftTopCard; 
					slot = &m_leftTopCard; 
					slotRect = &m_leftTopCardRect;
				} else if (World::PointInRect(mouse, m_leftBottomCardRect)) { 
					card = m_leftBottomCard; 
					slot = &m_leftBottomCard;
					slotRect = &m_leftBottomCardRect;
				}
			} else if (m_turn == TEAMS::RIGHT) {
				if (World::PointInRect(mouse, m_rightTopCardRect)) {
					card = m_rightTopCard; 
					slot = &m_rightTopCard; 
					slotRect = &m_rightTopCardRect;
				} else if (World::PointInRect(mouse, m_rightBottomCardRect)) { 
					card = m_rightBottomCard; 
					slot = &m_rightBottomCard;
					slotRect = &m_rightBottomCardRect;
				}
			}
			m_allowedTiles.clear();
			if (card != nullptr) {
				if (m_selectedCard == card) {
					m_selectedCard = nullptr;
				} else {
					m_selectedCard = card;
					m_selectedCardSlot = slot;
					m_selectedCardSlotRect = slotRect;
				}
			} else {
				m_selectedCard = nullptr;
			}
		}
	}
	m_winner = winCondition();
}

void Grid::draw(){
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			m_tiles[r][c].draw();
		}
	}
	for (Tile* tp : m_allowedTiles) {
		SDL_RenderCopy(m_renderer, TextureManager::m_allowedTile, NULL, tp->m_rect);
	}
	for (auto& p : m_pawns) {
		p->draw();
	}

	//draw cards
	if(m_leftTopCard != nullptr){SDL_RenderCopy(m_renderer, m_leftTopCard->getTexture(), NULL, &m_leftTopCardRect);}
	if (m_leftBottomCard != nullptr){SDL_RenderCopy(m_renderer, m_leftBottomCard->getTexture(), NULL, &m_leftBottomCardRect);}
	if (m_rightTopCard != nullptr){SDL_RenderCopy(m_renderer, m_rightTopCard->getTexture(), NULL, &m_rightTopCardRect);}
	if (m_rightBottomCard != nullptr){SDL_RenderCopy(m_renderer, m_rightBottomCard->getTexture(), NULL, &m_rightBottomCardRect);}
	if (m_toLeftCard != nullptr){SDL_RenderCopy(m_renderer, m_toLeftCard->getTexture(), NULL, &m_toLeftCardRect);}
	if (m_toRightCard != nullptr) { SDL_RenderCopy(m_renderer, m_toRightCard->getTexture(), NULL, &m_toRightCardRect); }

	if (m_selectedCard != nullptr) {
		SDL_RenderCopy(m_renderer, TextureManager::m_selectedCard, NULL, &m_selectedCard->m_rect);
	}

	//draw turn coins
	if (m_turn == TEAMS::LEFT) {
		SDL_RenderCopy(m_renderer, TextureManager::m_leftTurnCoin, NULL, &ConfigManager::m_Player_1_On_Turn_Rect);
	} else if (m_turn == TEAMS::RIGHT) {
		SDL_RenderCopy(m_renderer, TextureManager::m_rightTurnCoin, NULL, &ConfigManager::m_Player_2_On_Turn_Rect);
	}
}

TEAMS Grid::nextTeam(TEAMS t) {
	switch (t) {
	case TEAMS::LEFT: {
		return TEAMS::RIGHT;
	}break;
	case TEAMS::RIGHT: {
		return TEAMS::LEFT;
	}break;
	}
}

TEAMS Grid::winCondition() {
	Tile* leftTemple = &m_tiles[2][0];
	Tile* rightTemple = &m_tiles[2][4];
	int leftPawnCounter = 0;
	int rightPawnCounter = 0;
	int leftSenseiCounter = 0;
	int rightSenseiCounter = 0;
	for (Pawn*& p : m_pawns) {
		//count players
		if (p->m_team == TEAMS::LEFT) {
			if (p->m_role == PAWN_ROLES::PAWN) { leftPawnCounter++; }
			else if(p->m_role == PAWN_ROLES::SENSEI) { leftSenseiCounter++; }
		} else if (p->m_team == TEAMS::RIGHT) {
			if (p->m_role == PAWN_ROLES::PAWN) { rightPawnCounter++; }
			else if (p->m_role == PAWN_ROLES::SENSEI) { rightSenseiCounter++; }
		}
		// in temple
		if (p->m_team == TEAMS::LEFT && p->m_tile == &m_tiles[2][4]) {
			return TEAMS::LEFT;
		} else if (p->m_team == TEAMS::RIGHT && p->m_tile == &m_tiles[2][0]){
			return TEAMS::RIGHT;
		}
	}
	//check no sensei
	if (leftSenseiCounter == 0) { return TEAMS::RIGHT; }
	else if (rightSenseiCounter == 0) { return TEAMS::LEFT; }
	//check no pawns
	if (leftPawnCounter == 0) { return TEAMS::RIGHT; }
	else if (rightPawnCounter == 0) { return TEAMS::LEFT; }

	return TEAMS::NONE;
}

std::vector<CARDTYPES> Grid::chooseRandomCards(int count) {
	assert(ConfigManager::m_cards.size() > count);
	std::set<int> choices;
	std::vector<CARDTYPES> cards;
	int choice;
	while(choices.size() < count){
		choice = rand() % ConfigManager::m_cards.size();
		if (choices.count(choice) > 0) { continue; }
		choices.insert(choice);
		cards.push_back(ConfigManager::m_cards[choice]);
	}
	return cards;
}