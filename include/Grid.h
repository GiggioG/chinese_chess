#pragma	once
#include <vector>
#include "Tile.h"
#include "Pawn.h"
#include "Card.h"
class Grid {
public:
	Grid();
	~Grid();

	SDL_Renderer* m_renderer;
	int m_screenWidth;
	int m_screenHeight;
	Tile** m_tiles;
	std::vector<Pawn*> m_pawns;
	Pawn* m_selectedPawn = nullptr;
	std::vector<Tile*> m_allowedTiles;
	Card* m_selectedCard = nullptr;
	Card** m_selectedCardSlot = nullptr;
	SDL_Rect* m_selectedCardSlotRect = nullptr;
	TEAMS m_turn = TEAMS::LEFT;
	TEAMS m_winner = TEAMS::NONE;

	Card* m_leftTopCard;
	Card* m_leftBottomCard;
	Card* m_rightTopCard;
	Card* m_rightBottomCard;
	Card* m_toLeftCard;
	Card* m_toRightCard;
	SDL_Rect m_leftTopCardRect = {-1, -1, -1, -1};
	SDL_Rect m_leftBottomCardRect = {-1, -1, -1, -1};
	SDL_Rect m_rightTopCardRect = {-1, -1, -1, -1};
	SDL_Rect m_rightBottomCardRect = {-1, -1, -1, -1};
	SDL_Rect m_toLeftCardRect = {-1, -1, -1, -1};
	SDL_Rect m_toRightCardRect = {-1, -1, -1, -1};

	void init(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	void generateAllowed(Coord curr, Card* card, TEAMS team);
	void nextTurn();
	TEAMS nextTeam(TEAMS t);
	void update();
	void draw();
	TEAMS winCondition();
	std::vector<CARDTYPES> chooseRandomCards(int count);
};