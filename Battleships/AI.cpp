#include "AI.h"

#include "Utils.h"
#include <random>

AI::AI(Board& board, Board& playerBoard):m_aiBoard(board), m_playerBoard(playerBoard)
{
    placeShips();
}

void AI::doTurn() {
	unsigned int x = 0;
	unsigned int y = 0;

	switch (gameDifficulty) {
		// Truly Random
	case Difficulty::Easy: {
		int* pos = randomTurn();
        x = pos[0];
        y = pos[1];
        delete pos;
	}break;

		// Some Intelligence
	case Difficulty::Medium: {
		int option = randomInt(0, 1);
		switch (option) {
			// Random
		case 0: {
			int* pos = randomTurn();
            x = pos[0];
            y = pos[1];
            delete pos;
		}break;

			// Use m_hitSpots
		case 1: {
			int* pos = smartTurn();
            x = pos[0];
            y = pos[1];
            delete pos;
		}break;
		}
	}break;

		// Intelligence
	case Difficulty::Hard: {
		int option = randomInt(0, 3);
		switch (option) {
			// Corners
		case 0: {
			int* pos = cornerTurn();
            x = pos[0];
            y = pos[1];
            delete pos;
		}break;

			// Center
		case 1: {
			int* pos = centerTurn();
            x = pos[0];
            y = pos[1];
            delete pos;
		}break;

			// Use m_hitSpots
		case 2: {
			int* pos = smartTurn();
			x = pos[0];
			y = pos[1];
            delete pos;
		}break;

			// Random
		case 3: {
			int* pos = randomTurn();
            x = pos[0];
            y = pos[1];
            delete pos;
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

	if (m_playerBoard.getShip(x, y).damaged) {
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
			int horPos = randomInt(0, m_aiBoard.getBoardSize() - shipSize);
			int verPos = randomInt(0, m_aiBoard.getBoardSize() - 1);

			horizontal = randomInt(0, 1);

            x = horizontal ? horPos : verPos;
            y = horizontal ? verPos : horPos;

            previousShipTypes = m_aiBoard.getShipTypes(x, y, shipSize, horizontal);
            m_aiBoard.setShipType(x, y, currentShipType, shipSize, horizontal);

            if (!m_aiBoard.anyOverlap()) {
                break;
            }

            m_aiBoard.setShipTypes(x, y, previousShipTypes, horizontal);
        }

        currentShipType = (ShipType)++currentShipTypeInt;
    }
}

int* AI::randomTurn()
{
    int* toReturn = new int[2];
    unsigned int x = 0;
    unsigned int y = 0;

    x = randomInt(0, m_aiBoard.getBoardSize() - 1);
    y = randomInt(0, m_aiBoard.getBoardSize() - 1);


    toReturn[0] = x;
    toReturn[1] = y;
    return toReturn;
}

int* AI::cornerTurn()
{
    int* toReturn = new int[2];
    unsigned int x = 0;
    unsigned int y = 0;

    x = randomInt(0, 1) * (m_playerBoard.getBoardSize() - 1);
    y = randomInt(0, 1) * (m_playerBoard.getBoardSize() - 1);

    toReturn[0] = x;
    toReturn[1] = y;
    return toReturn;
}

int* AI::centerTurn()
{
    int* toReturn = new int[2];
    unsigned int x = 0;
    unsigned int y = 0;

    // Get the center tile
    int middle = m_playerBoard.getBoardSize() / 2;
    // Get how wide the center should be
    int width = m_playerBoard.getBoardSize() / 4;

    x = randomInt(width, middle + width);
    y = randomInt(width, middle + width);

    toReturn[0] = x;
    toReturn[1] = y;
    return toReturn;
}

int* AI::smartTurn()
{
    int* toReturn = new int[2];
    unsigned int x = 0;
    unsigned int y = 0;

    // if the AI hasnt hit any places yet, do a random turn
    if (m_hitSpots.size() <= 0) {
        delete toReturn;
        return randomTurn();
    }

    int index = randomInt(0, (m_hitSpots.size() / 2) - 1) * 2;

    unsigned int hitX = m_hitSpots.at(index);
    unsigned int hitY = m_hitSpots.at(index + 1);

	int option = randomInt(0, 7);

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
        delete toReturn;
        return smartTurn();
    }

    toReturn[0] = x;
    toReturn[1] = y;
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
