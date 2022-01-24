#include "Utilities.h"

#include <conio.h>
#include <iostream>

HANDLE Utilities::hConsole;
Difficulty Utilities::m_difficulty;

void Utilities::init() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Utilities::setColor(WORD wAttributes) {
	SetConsoleTextAttribute(hConsole, wAttributes);
}

void Utilities::resetColor() {
	setColor(LIGHT_GREY);
}

int Utilities::getInput() {
	return _getch();
}


Difficulty Utilities::getDifficulty() {
	return m_difficulty;
}

void Utilities::setDifficulty(Difficulty difficulty) {
	m_difficulty = difficulty;
}

void Utilities::setShipType(Board& board, unsigned int x, unsigned int y, ShipType shipType, unsigned int shipSize, bool horizontal) {
    for (size_t i = 0; i < shipSize; i++)
    {
        Ship* ship = board.getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
        if (ship->getType() != shipType && ship->getType() != ShipType::Null) {
            ship->setDamaged(true);
        }
        else {
            ship->setDamaged(false);
        }
        ship->setType(shipType);
    }
}

void Utilities::setShipType(Board& board, unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal)
{
    for (size_t i = 0; i < shipTypes.size(); i++)
    {
        Ship* ship = board.getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
        ship->setDamaged(false);
        ship->setType(shipTypes.at(i));
    }
}

std::vector<ShipType> Utilities::getShipTypes(Board& board, unsigned int x, unsigned int y, unsigned int shipSize, bool horizontal) {
    std::vector<ShipType> shipTypes;
    for (size_t i = 0; i < shipSize; i++)
    {
        shipTypes.push_back(board.getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i))->getType());
    }
    return shipTypes;
}

void Utilities::updateShipSelection(Board& board, ShipType& previousShipType, unsigned int x, unsigned int y) {
    previousShipType = board.getShip(x, y)->getType();
    if (previousShipType == ShipType::Null || (previousShipType == ShipType::Shot && !board.getShip(x, y)->isDamaged())) {
        board.getShip(x, y)->setType(ShipType::SelectorOcean);
    }
    else {
        board.getShip(x, y)->setType(ShipType::Selector);
    }
}

/*
Very hacky way of checking for overlays
*/
bool Utilities::anyOverlay(Board& board) {
    for (size_t y = 0; y < board.getBoardSize(); y++)
    {
        for (size_t x = 0; x < board.getBoardSize(); x++)
        {
            if (board.getShip(x, y)->isDamaged())
                return true;
        }
    }
    return false;
}

bool Utilities::allDestroyed(Board& board)
{
    for (size_t y = 0; y < board.getBoardSize(); y++)
    {
        for (size_t x = 0; x < board.getBoardSize(); x++)
        {
            Ship* ship = board.getShip(x, y);
            if (ship->getType() == ShipType::Null || ship->getType() == ShipType::Selector || ship->getType() == ShipType::SelectorOcean)
                continue;
            if (!board.getShip(x, y)->isDamaged())
                return false;
        }
    }
    return true;
}