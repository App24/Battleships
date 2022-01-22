#pragma once
#include "Board.h"
#include <vector>

class Game {
public:
	Game();

	void setupBoard();

	Board* getPlayerBoard();
	Board* getAIBoard();
private:
	Board m_playerBoard, m_aiBoard;

	void setShipType(Board& board, unsigned int x, unsigned int y, ShipType shipType, unsigned int shipSize, bool horizontal);
	void setShipType(Board& board, unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal);

	std::vector<ShipType> getShipTypes(Board& board, unsigned int x, unsigned int y, unsigned int shipSize, bool horizontal);

	bool anyOverlay(Board& board);
};