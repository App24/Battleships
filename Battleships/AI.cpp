#include "AI.h"
#include "Utilities.h"
#include <random>

AI::AI(Board& board, Board& playerBoard):m_aiBoard(board), m_playerBoard(playerBoard)
{
    placeShips();
}

void AI::doTurn() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 3);

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
        int option = dist1(rng);
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
        int option = dist3(rng);
        switch (option) {
            // Do Corners
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

    if (hasAttacked(x,y)) {
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
    /*for (size_t y = 0; y < m_aiBoard.getBoardSize(); y++)
    {
        for (size_t x = 0; x < m_aiBoard.getBoardSize(); x++)
        {
            m_aiBoard.getShip(x, y)->setType((ShipType)((y * m_aiBoard.getBoardSize() + x) % 6));
        }
    }*/

    std::random_device dev;
    std::mt19937 rng(dev());

    ShipType currentShipType = (ShipType)1;
    for (size_t i = 0; i < 5; i++)
    {
        // Place idk
        int currentShipTypeInt = (int)currentShipType;

        int shipSize = shipSizes[currentShipTypeInt];
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);

        bool horizontal = false;

        unsigned int x = 0;
        unsigned int y = 0;
        std::vector<ShipType> previousShipTypes;

        while(1) {
            std::uniform_int_distribution<std::mt19937::result_type> distHor(0, 9 - shipSize);
            std::uniform_int_distribution<std::mt19937::result_type> distVer(0, 9);

            horizontal = dist1(rng);

            x = horizontal ? distHor(rng) : distVer(rng);
            y = horizontal ? distVer(rng) : distHor(rng);

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

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist9(0, 9);

    x = dist9(rng);
    y = dist9(rng);


    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::cornerTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);

    x = dist1(rng) * (m_playerBoard.getBoardSize() - 1);
    y = dist1(rng) * (m_playerBoard.getBoardSize() - 1);

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::centerTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    int middle = m_playerBoard.getBoardSize() / 2;
    int width = m_playerBoard.getBoardSize() / 4;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(width, middle+width);

    x = dist(rng);
    y = dist(rng);

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

std::vector<int> AI::smartTurn()
{
    std::vector<int> toReturn;
    unsigned int x = 0;
    unsigned int y = 0;

    if (m_hitSpots.size() <= 0) {
        return randomTurn();
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, (m_hitSpots.size() / 2) - 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 7);

    int index = dist(rng) * 2;

    unsigned int hitX = m_hitSpots.at(index);
    unsigned int hitY = m_hitSpots.at(index + 1);

    int option = dist3(rng);

    switch (option)
    {
    case 0: {
        x = hitX - 1;
        y = hitY - 1;
    }break;

    case 1: {
        x = hitX;
        y = hitY - 1;
    }break;

    case 2: {
        x = hitX + 1;
        y = hitY - 1;
    }break;

    case 3: {
        x = hitX - 1;
        y = hitY;
    }break;

    case 4: {
        x = hitX + 1;
        y = hitY;
    }break;

    case 5: {
        x = hitX - 1;
        y = hitY + 1;
    }break;

    case 6: {
        x = hitX;
        y = hitY + 1;
    }break;

    case 7: {
        x = hitX + 1;
        y = hitY + 1;
    }break;

    }

    if (hasAttacked(x, y)) {
        return smartTurn();
    }

    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

bool AI::hasAttacked(unsigned int x, unsigned int y)
{
    if(m_attackedSpots.size()<=0)
    return false;

    for (size_t i = 0; i < m_attackedSpots.size()/2; i+=2)
    {
        unsigned int attackX = m_attackedSpots.at(i);
        unsigned int attackY = m_attackedSpots.at(i+1);
        if (attackX == x && attackY == y)
            return true;
    }

    return false;
}
