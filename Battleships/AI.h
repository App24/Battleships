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

	// Coords of spots that have been successfully hit and spots that have been attacked
	std::vector<int> m_hitSpots, m_attackedSpots;

	// Different things the AI can do depending on the difficulty
	std::vector<int> randomTurn();
	std::vector<int> cornerTurn();
	std::vector<int> centerTurn();
	std::vector<int> smartTurn();

	// Allows to check if the AI has attacked one spot already
	bool hasAttacked(unsigned int x, unsigned int y);
};