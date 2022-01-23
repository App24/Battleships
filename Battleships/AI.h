#pragma once
#include "Board.h"
#include <vector>

class AI {
public:
	AI(Board& aiBoard, Board& playerBoard);

	void doTurn();
private:
	void placeShips();

	Board& m_aiBoard, m_playerBoard;

	std::vector<int> m_hitSpots, m_attackedSpots;

	std::vector<int> randomTurn();
	std::vector<int> cornerTurn();
	std::vector<int> centerTurn();
	std::vector<int> smartTurn();

	bool hasAttacked(unsigned int x, unsigned int y);
};