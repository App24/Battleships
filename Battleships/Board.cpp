#include "Board.h"

#include <stdlib.h>
#include <cstring>

#include <iostream>

#include "Utils.h"

Board::Board(unsigned int boardSize) : m_boardSize(boardSize)
{
	m_ships = new Ship[boardSize * boardSize];
	memset(m_ships, 0, boardSize * boardSize * sizeof(Ship));
}

Board::Board() : Board(10)
{
}


Ship* Board::getShips()
{
	return m_ships;
}

Ship& Board::getShip(unsigned int x, unsigned int y)
{
	if (x >= m_boardSize || y >= m_boardSize) {
		Ship ship;
		return ship;
	}
	return m_ships[y * m_boardSize + x];
}

void Board::show()
{
	for (int y = -1; y < (int)m_boardSize; y++)
	{
		for (int x = -1; x < (int)m_boardSize; x++)
		{
			if (x == -1 && y == -1) {
				std::cout << "  |";
			}
			else if (x == -1 && y >= 0) {
				int line = y + 1;
				setColor(DARK_YELLOW);
				std::cout << line;
				if (line < 10)
					std::cout << " ";
				resetColor();
				std::cout << "|";
			}
			else if (y == -1 && x >= 0) {
				setColor(DARK_CYAN);
				std::cout << " " << (char)(65 + x);
				resetColor();
				std::cout << " |";
			}
			else {
				Ship ship = getShip(x, y);
				std::string repr = shortShipString[(int)ship.shipType];
				if (ship.damaged) {
					if (ship.shipType == ShipType::Selection || ship.shipType == ShipType::WaterSelection) {
						setColor(GET_BACKGROUND(WHITE, DARK_GREY));
					}
					else {
						setColor(GET_BACKGROUND(DARK_RED, DARK_GREY));
					}
				}
				else {
					if (ship.shipType == ShipType::Empty || ship.shipType == ShipType::WaterSelection || ship.shipType == ShipType::Shot) {
						setColor(GET_BACKGROUND(WHITE, DARK_BLUE));
					}
					else {
						setColor(GET_BACKGROUND(WHITE, DARK_GREY));
					}
				}
				std::cout << repr;
				if (repr.length() < 3) {
					for (size_t i = 0; i < 3 - repr.length(); i++)
					{
						std::cout << " ";
					}
				}

				if (x < m_boardSize - 1)
					setColor(GET_BACKGROUND(WHITE, DARK_BLUE));
				else
					resetColor();

				std::cout << "|";
				resetColor();
			}
		}

		std::cout << std::endl;
	}
}

bool Board::hitShip(unsigned int x, unsigned int y)
{
	Ship& ship = getShip(x, y);
	if (ship.shipType == ShipType::Empty)
		return false;
	if (ship.damaged)
		return false;
	ship.damaged = true;
	return true;
}

std::vector<ShipType> Board::getShipTypes(unsigned int x, unsigned int y, int amount, bool horizontal)
{
	std::vector<ShipType> shipTypes;
	for (size_t i = 0; i < amount; i++)
	{
		shipTypes.push_back(getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i)).shipType);
	}
	return shipTypes;
}

void Board::setShipType(unsigned int x, unsigned int y, ShipType shipType, int amount, bool horizontal)
{
	for (size_t i = 0; i < amount; i++)
	{
		Ship& ship = getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
		if (ship.shipType != shipType && ship.shipType != ShipType::Empty)
			ship.damaged = true;
		else
			ship.damaged = false;
		ship.shipType = shipType;
	}
}

void Board::setShipTypes(unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal)
{
	for (size_t i = 0; i < shipTypes.size(); i++)
	{
		Ship& ship = getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
		ship.damaged = false;
		ship.shipType = shipTypes[i];
	}
}

void Board::updateShipSelection(ShipType& previousShipType, unsigned int x, unsigned int y)
{
	previousShipType = getShip(x, y).shipType;
	if (previousShipType == ShipType::Empty || (previousShipType == ShipType::Shot && !getShip(x, y).damaged)) {
		getShip(x, y).shipType=ShipType::WaterSelection;
	}
	else {
		getShip(x, y).shipType=ShipType::Selection;
	}
}