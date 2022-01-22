#pragma once
#include "Board.h"

class AI {
public:
	AI(Board& aiBoard, Board& playerBoard);

	void doTurn();
private:
	void placeShips();

	Board& m_aiBoard, m_playerBoard;
};