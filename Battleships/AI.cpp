#include "AI.h"

#include "Utilities.h"
#include <random>

AI::AI(Board& board, Board& playerBoard):m_aiBoard(board), m_playerBoard(playerBoard)
{
    placeShips();
}

void AI::doTurn() {
	unsigned int x = 0;
	unsigned int y = 0;

	switch (Utilities::getDifficulty()) {
		// Truly Random
	case Difficulty::Easy: {
		std::vector<int> pos = randomTurn();
		x = pos.at(0);
		y = pos.at(1);
	}break;

		// Some Intelligence
	case Difficulty::Medium: {
		int option = Utilities::randomInt(0, 1);
		switch (option) {
			// Random
		case 0: {
			std::vector<int> pos = randomTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;

			// Use m_hitSpots
		case 1: {
			std::vector<int> pos = smartTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;
		}
	}break;

		// Intelligence
	case Difficulty::Hard: {
		int option = Utilities::randomInt(0, 3);
		switch (option) {
			// Corners
		case 0: {
			std::vector<int> pos = cornerTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;

			// Center
		case 1: {
			std::vector<int> pos = centerTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;

			// Use m_hitSpots
		case 2: {
			std::vector<int> pos = smartTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;

			// Random
		case 3: {
			std::vector<int> pos = randomTurn();
			x = pos.at(0);
			y = pos.at(1);
		}break;
		}
	}break;
	}

	if (x < 0 || y < 0 || x >= m_playerBoard.getBoardSize() || y >= m_playerBoard.getBoardSize()) {
		doTurn();
		return;
	}

	if (hasAttacked(x, y)) {
		doTurn();
		return;
	}

	if (m_playerBoard.getShip(x, y)->isDamaged()) {
		doTurn();
		return;
	}

	if (m_playerBoard.hitShip(x, y)) {
		m_hitSpots.push_back(x);
		m_hitSpots.push_back(y);
	}

	m_attackedSpots.push_back(x);
	m_attackedSpots.push_back(y);
}

void AI::placeShips()
{
    ShipType currentShipType = (ShipType)1;
    for (size_t i = 0; i < 5; i++)
    {
        int currentShipTypeInt = (int)currentShipType;

        int shipSize = shipSizes[currentShipTypeInt];

        bool horizontal = false;

        unsigned int x = 0;
        unsigned int y = 0;
        std::vector<ShipType> previousShipTypes;

        while(1) {
			int horPos = Utilities::randomInt(0, m_aiBoard.getBoardSize() - shipSize);
			int verPos = Utilities::randomInt(0, m_aiBoard.getBoardSize() - 1);

			horizontal = Utilities::randomInt(0, 1);

            x = horizontal ? horPos : verPos;
            y = horizontal ? verPos : horPos;

            previousShipTypes = Utilities::getShipTypes(m_aiBoard, x, y, shipSize, horizontal);
            Utilities::setShipType(m_aiBoard, x, y, currentShipType, shipSize, horizontal);

            if (!Utilities::anyOverlay(m_aiBoard)) {
                break;
            }

            Utilities::setShipType(m_aiBoard, x, y, previousShipTypes, horizontal);
        }

        currentShipType = (ShipType)++currentShipTypeInt;
    }
}

std::vector<int> AI::randomTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    x = Utilities::randomInt(0, m_aiBoard.getBoardSize() - 1);
    y = Utilities::randomInt(0, m_aiBoard.getBoardSize() - 1);


    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::cornerTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    x = Utilities::randomInt(0, 1) * (m_playerBoard.getBoardSize() - 1);
    y = Utilities::randomInt(0, 1) * (m_playerBoard.getBoardSize() - 1);

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::centerTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    // Get the center tile
    int middle = m_playerBoard.getBoardSize() / 2;
    // Get how wide the center should be
    int width = m_playerBoard.getBoardSize() / 4;

    x = Utilities::randomInt(width, middle + width);
    y = Utilities::randomInt(width, middle + width);

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::smartTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    // if the AI hasnt hit any places yet, do a random turn
    if (m_hitSpots.size() <= 0) {
        return randomTurn();
    }

    int index = Utilities::randomInt(0, (m_hitSpots.size() / 2) - 1) * 2;

    unsigned int hitX = m_hitSpots.at(index);
    unsigned int hitY = m_hitSpots.at(index + 1);

	int option = Utilities::randomInt(0, 7);

    switch (option)
    {
        // Top Left from the center
    case 0: {
        x = hitX - 1;
        y = hitY - 1;
    }break;

        // Top Middle from the center
    case 1: {
        x = hitX;
        y = hitY - 1;
    }break;

        // Top Right from the center
    case 2: {
        x = hitX + 1;
        y = hitY - 1;
    }break;

        // Middle Left from the center
    case 3: {
        x = hitX - 1;
        y = hitY;
    }break;

        // Middle Right from the center
    case 4: {
        x = hitX + 1;
        y = hitY;
    }break;
        
        // Bottom Left from the center
    case 5: {
        x = hitX - 1;
        y = hitY + 1;
    }break;

        // Bottom Middle from the center
    case 6: {
        x = hitX;
        y = hitY + 1;
    }break;

        // Bottom Right from the center
    case 7: {
        x = hitX + 1;
        y = hitY + 1;
    }break;

    }

    // If the AI has attacked that place already, get a new place to attack
    // Potential infinite loop?
    if (hasAttacked(x, y)) {
        return smartTurn();
    }

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

bool AI::hasAttacked(unsigned int x, unsigned int y)
{
    if (m_attackedSpots.size() <= 0)
        return false;

    for (size_t i = 0; i < m_attackedSpots.size() / 2; i += 2)
    {
        unsigned int attackX = m_attackedSpots.at(i);
        unsigned int attackY = m_attackedSpots.at(i + 1);
        if (attackX == x && attackY == y)
            return true;
    }

    return false;
}
