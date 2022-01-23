#include "Board.h"

#include "Utilities.h"
#include <iostream>

Board::Board(unsigned int boardSize) : m_boardSize(boardSize) {
	m_ships = new Ship[boardSize * boardSize];
	for (unsigned int y = 0; y < boardSize; y++)
	{
		for (unsigned int x = 0; x < boardSize; x++)
		{
			m_ships[y * m_boardSize + x] = Ship();
		}
	}
}

Board::Board() : Board(10) {

}

Ship* Board::getShips() {
	return m_ships;
}

Ship* Board::getShip(unsigned int x, unsigned int y) {
	if (x >= m_boardSize || y >= m_boardSize) {
		return nullptr;
	}
	return &m_ships[y * m_boardSize + x];
}

unsigned int Board::getBoardSize() {
	return m_boardSize;
}

void Board::showBoard() {
	for (int y = -1; y < (int)m_boardSize; y++)
	{
		for (int x = -1; x < (int)m_boardSize; x++)
		{
			if (x == -1 && y == -1) {
				std::cout << "  |";
			}
			else if (y == -1 && x >= 0) {
				Utilities::setColor(DARK_CYAN);
				std::cout << " " << (char)(65 + x);
				Utilities::resetColor();
				std::cout << " |";
			}
			else if (x == -1 && y >= 0) {
				int line = y + 1;
				Utilities::setColor(DARK_YELLOW);
				std::cout << line;
				if (line < 10)
					std::cout << " ";
				Utilities::resetColor();
				std::cout << "|";
			}
			else {
				Ship* ship = getShip(x, y);
				std::string repr = ship->getStrRepr();
				if (ship->isDamaged()) {
					if (ship->getType() == ShipType::Selector || ship->getType() == ShipType::SelectorOcean) {
						Utilities::setColor(GET_BACKGROUND(WHITE, DARK_GREY));
					}
					else {
						Utilities::setColor(GET_BACKGROUND(DARK_RED, DARK_GREY));
					}
				}
				else {
					if (ship->getType() == ShipType::Null||ship->getType()==ShipType::SelectorOcean||ship->getType()==ShipType::Shot)
						Utilities::setColor(GET_BACKGROUND(WHITE, DARK_BLUE));
					else
						Utilities::setColor(GET_BACKGROUND(WHITE, DARK_GREY));
				}
				std::cout << repr;
				if (repr.length() < 3) {
					for (size_t i = 0; i < 3 - repr.length(); i++)
					{
						std::cout << " ";
					}
				}
				if (x < m_boardSize - 1)
					Utilities::setColor(GET_BACKGROUND(WHITE, DARK_BLUE));
				else
					Utilities::resetColor();
				std::cout << "|";
				Utilities::resetColor();
			}
		}

		std::cout << std::endl;
	}
}

bool Board::hitShip(unsigned int x, unsigned int y) {
	Ship* ship = getShip(x, y);
	if (ship->getType() == ShipType::Null)
		return false;
	if (ship->isDamaged())
		return false;
	ship->setDamaged(true);
	return true;
}