#pragma once
#include "Ship.h"

class Board {
public:
	Board(unsigned int boardSize);
	Board();

	Ship* getShips();

	Ship* getShip(unsigned int x, unsigned int y);

	unsigned int getBoardSize();

	void showBoard();

	std::string getStrPos(unsigned int x, unsigned int y);

	bool hitShip(unsigned int x, unsigned int y);
private:
	Ship* m_ships;
	unsigned int m_boardSize;
};