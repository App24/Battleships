#include "Game.h"
#include "Utilities.h"
#include <iostream>

Game::Game() {

}

void Game::setupBoard() {
    unsigned int x = 0;
    unsigned int y = 0;
    ShipType currentShipType = (ShipType)1;
    std::vector<ShipType> previousShipTypes;
    bool selectMode = true;
    Ship* origBoard = m_playerBoard.getShips();
    int* remainingShips = new int[6]{ 0, 1, 1, 1, 1, 1 };
    int* shipSizes = new int[6]{ 0, 2, 3, 3, 4, 5 };
    bool horizontal = true;
    bool finished = false;
    while (!finished) {
        if (remainingShips[(int)currentShipType] <= 0) {
            Utilities::setColor(DARK_RED);
        }
        else if (selectMode) {
            Utilities::setColor(GREEN);
        }
        std::cout << ship_type_str[(int)currentShipType] << std::endl;

        Utilities::setColor(DARK_CYAN);
        std::cout << (char)(65 + x) << " ";

        Utilities::setColor(DARK_YELLOW);
        std::cout << (y + 1) << std::endl;

        Utilities::resetColor();

        m_playerBoard.showBoard();

        int c = Utilities::getInput();

        if (selectMode) {
            switch (c)
            {
            case KEY_LEFT: {
                int currentShipTypeInt = (int)currentShipType;
                if (currentShipTypeInt > 1)
                    currentShipType = (ShipType)--currentShipTypeInt;
            }break;

            case KEY_RIGHT: {
                int currentShipTypeInt = (int)currentShipType;
                if (currentShipTypeInt < 5)
                    currentShipType = (ShipType)++currentShipTypeInt;
            }break;

            case KEY_ENTER: {
                if (remainingShips[(int)currentShipType] > 0) {
                    selectMode = false;
                    previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_ESCAPE: {
                finished = true;
            }break;
            }
        }
        else {
            switch (c)
            {
            case KEY_R: {
                setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                horizontal = !horizontal;
                if (horizontal && x >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    x = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                else if (!horizontal && y >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    y = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
            }break;

            case KEY_ESCAPE: {
                selectMode = true;
                setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
            }break;

            case KEY_ENTER: {
                if (!anyOverlay(m_playerBoard)) {
                    remainingShips[(int)currentShipType]--;
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                    x = 0;
                    y = 0;
                    selectMode = true;
                }
            }break;

            case KEY_LEFT: {
                if (x > 0) {
                    setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    x--;
                    previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_RIGHT: {
                if (x < m_playerBoard.getBoardSize() - (horizontal ? shipSizes[(int)currentShipType] : 1)) {
                    setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    x++;
                    previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_UP: {
                if (y > 0) {
                    setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    y--;
                    previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_DOWN: {
                if (y < m_playerBoard.getBoardSize() - (horizontal ? 1 : shipSizes[(int)currentShipType])) {
                    setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    y++;
                    previousShipTypes = getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;
            }
        }

        system("cls");
    }

    playGame();
}

void Game::playGame()
{
    unsigned int x = 0;
    unsigned int y = 0;
    ShipType previousShipType = m_playerBoard.getShip(x, y)->getType();
    updateShipSelection(m_playerBoard, previousShipType, x, y);
    while (1) {
        m_playerBoard.showBoard();

        int c = Utilities::getInput();

        switch (c)
        {
        case KEY_LEFT: {
            if (x > 0) {
                m_playerBoard.getShip(x, y)->setType(previousShipType);
                x--;
                updateShipSelection(m_playerBoard, previousShipType, x, y);
            }
        }break;

        case KEY_RIGHT: {
            if (x < m_playerBoard.getBoardSize() - 1) {
                m_playerBoard.getShip(x, y)->setType(previousShipType);
                x++;
                updateShipSelection(m_playerBoard, previousShipType, x, y);
            }
        }break;


        case KEY_UP: {
            if (y > 0) {
                m_playerBoard.getShip(x, y)->setType(previousShipType);
                y--;
                updateShipSelection(m_playerBoard, previousShipType, x, y);
            }
        }break;

        case KEY_DOWN: {
            if (y < m_playerBoard.getBoardSize() - 1) {
                m_playerBoard.getShip(x, y)->setType(previousShipType);
                y++;
                updateShipSelection(m_playerBoard, previousShipType, x, y);
            }
        }break;

        case KEY_ENTER: {
            if (previousShipType != ShipType::Null&&!m_playerBoard.getShip(x,y)->isDamaged()) {
                m_playerBoard.getShip(x, y)->setDamaged(true);
            }
        }break;
        }

        system("cls");
    }
}

Board& Game::getPlayerBoard() {
    return m_playerBoard;
}

Board& Game::getAIBoard() {
    return m_aiBoard;
}

void Game::setShipType(Board& board, unsigned int x, unsigned int y, ShipType shipType, unsigned int shipSize, bool horizontal) {
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

void Game::setShipType(Board& board, unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal)
{
    for (size_t i = 0; i < shipTypes.size(); i++)
    {
        Ship* ship = board.getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
        ship->setDamaged(false);
        ship->setType(shipTypes.at(i));
    }
}

std::vector<ShipType> Game::getShipTypes(Board& board, unsigned int x, unsigned int y, unsigned int shipSize, bool horizontal) {
    std::vector<ShipType> shipTypes;
    for (size_t i = 0; i < shipSize; i++)
    {
        shipTypes.push_back(board.getShip(x + (horizontal ? i : 0), y + (horizontal ? 0 : i))->getType());
    }
    return shipTypes;
}

/*
Very hacky way of checking for overlays
*/
bool Game::anyOverlay(Board& board) {
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

void Game::updateShipSelection(Board& board, ShipType& previousShipType, unsigned int x, unsigned int y) {
    previousShipType = m_playerBoard.getShip(x, y)->getType();
    if (previousShipType == ShipType::Null)
        m_playerBoard.getShip(x, y)->setType(ShipType::SelectorOcean);
    else
        m_playerBoard.getShip(x, y)->setType(ShipType::Selector);
}