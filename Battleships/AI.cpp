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

    unsigned int x = 0;
    unsigned int y = 0;

    switch (Utilities::getDifficulty()) {
    case Difficulty::Easy: {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);

        x = dist6(rng);
        y = dist6(rng);
    }break;

    case Difficulty::Medium: {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);

        x = dist6(rng);
        y = dist6(rng);
    }break;

    case Difficulty::Hard: {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);

        x = dist6(rng);
        y = dist6(rng);
    }break;
    }

    if (m_playerBoard.getShip(x, y)->isDamaged()) {
        doTurn();
        return;
    }

    m_playerBoard.hitShip(x, y);
}

void AI::placeShips()
{
    for (size_t y = 0; y < m_aiBoard.getBoardSize(); y++)
    {
        for (size_t x = 0; x < m_aiBoard.getBoardSize(); x++)
        {
            m_aiBoard.getShip(x, y)->setType((ShipType)((y * m_aiBoard.getBoardSize() + x) % 6));
        }
    }
}
