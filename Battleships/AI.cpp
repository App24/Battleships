#include "AI.h"

AI::AI(Board& board):m_board(board)
{
    placeShips();
}

void AI::placeShips()
{
    for (size_t y = 0; y < m_board.getBoardSize(); y++)
    {
        for (size_t x = 0; x < m_board.getBoardSize(); x++)
        {
            m_board.getShip(x, y)->setType((ShipType)((y * m_board.getBoardSize() + x) % 6));
        }
    }
}
