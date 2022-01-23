#pragma once
#include "Ship.h"

class Board {
public:
	Board(unsigned int boardSize);
	Board();

	// Get a pointer to the ships on the board
	Ship* getShips();

	// Get a pointer to a ship at coord x and y
	Ship* getShip(unsigned int x, unsigned int y);

	// Get the board size
	unsigned int getBoardSize();

	// Print the board to the console
	void showBoard();

	// Hit a ship on the board at coord x and y
	bool hitShip(unsigned int x, unsigned int y);
private:
	Ship* m_ships;
	unsigned int m_boardSize;
};