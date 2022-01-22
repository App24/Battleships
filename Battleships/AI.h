#pragma once
#include "Board.h"

class AI {
public:
	AI(Board& board);
private:
	void placeShips();

	Board& m_board;
};