#pragma once

#include "Ship.h"
#include <vector>

class Board {
public:
	Board(unsigned int boardSize);
	Board();

	Ship* getShips();

	Ship& getShip(unsigned int x, unsigned int y);

	void show();

	bool hitShip(unsigned int x, unsigned int y);

	int getBoardSize() {
		return m_boardSize;
	}

	bool anyOverlap() {
		for (size_t i = 0; i < m_boardSize * m_boardSize; i++)
		{
			if (m_ships[i].damaged)
				return true;
		}
		return false;
	}

	bool allDestroyed() {
		for (size_t x = 0; x < m_boardSize; x++)
		{
			for (size_t y = 0; y < m_boardSize; y++)
			{
				Ship ship = getShip(x, y);
				if (ship.shipType == ShipType::Empty || ship.shipType == ShipType::Selection || ship.shipType == ShipType::WaterSelection)
					continue;
				if (!ship.damaged)
					return false;
			}
		}
		return true;
	}

	std::vector<ShipType> getShipTypes(unsigned int x, unsigned int y, int amount, bool horizontal);
	void setShipType(unsigned int x, unsigned int y, ShipType shipType, int amount, bool horizontal);
	void setShipTypes(unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal);

	void updateShipSelection(ShipType& previousShipType, unsigned int x, unsigned int y);

private:
	Ship* m_ships;
	unsigned int m_boardSize;
};