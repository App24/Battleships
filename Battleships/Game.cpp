#include "Game.h"
#include "Utilities.h"
#include <iostream>

Game::Game():m_ai(m_aiBoard, m_playerBoard) {

}

void Game::startGame()
{
    setDifficulty();
}

void Game::setDifficulty() {
    Difficulty currentDifficulty = (Difficulty)0;
    bool finished = false;
    int colors[] = { DARK_GREEN,YELLOW,DARK_RED };
    while (!finished) {
        int currentDifficultyInt = (int)currentDifficulty;
        std::cout << "Current Difficulty: ";
        Utilities::setColor(colors[currentDifficultyInt]);
        std::cout << difficulty_str[currentDifficultyInt] << std::endl;
        Utilities::resetColor();

        std::cout << std::endl;

        std::cout << "Change Selection: Arrow Keys" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;

        int c = Utilities::getInput();

        switch (c)
        {
        case KEY_LEFT: {
            if (currentDifficultyInt > 0)
                currentDifficulty = (Difficulty)--currentDifficultyInt;
        }break;

        case KEY_RIGHT: {
            if (currentDifficultyInt < 2)
                currentDifficulty = (Difficulty)++currentDifficultyInt;
        }break;

        case KEY_ENTER: {
            Utilities::setDifficulty(currentDifficulty);
            finished = true;
        }break;
        }

        system("cls");
    }

    setupBoard();
}

void Game::setupBoard() {
    unsigned int x = 0;
    unsigned int y = 0;
    ShipType currentShipType = (ShipType)1;
    std::vector<ShipType> previousShipTypes;
    bool selectMode = true;
    Ship* origBoard = m_playerBoard.getShips();
    int* remainingShips = new int[6]{ 0, 1, 1, 1, 1, 1 };
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

        std::cout << std::endl;

        std::cout << "Change/Move Selection: Arrow Keys" << std::endl;
        std::cout << "Rotate: R Key" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;
        std::cout << "Go Back/Finish: Escape Key" << std::endl;

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
                    previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_ESCAPE: {
                finished = true;
                for (size_t i = 0; i < 6; i++)
                {
                    if (remainingShips[i] > 0) {
                        finished = false;
                        break;
                    }
                }
            }break;
            }
        }
        else {
            switch (c)
            {
            case KEY_R: {
                Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                horizontal = !horizontal;
                if (horizontal && x >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    x = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                else if (!horizontal && y >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    y = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
            }break;

            case KEY_ESCAPE: {
                selectMode = true;
                Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
            }break;

            case KEY_ENTER: {
                if (!Utilities::anyOverlay(m_playerBoard)) {
                    remainingShips[(int)currentShipType]--;
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                    x = 0;
                    y = 0;
                    selectMode = true;
                }
            }break;

            case KEY_LEFT: {
                if (x > 0) {
                    Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    x--;
                    previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_RIGHT: {
                if (x < m_playerBoard.getBoardSize() - (horizontal ? shipSizes[(int)currentShipType] : 1)) {
                    Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    x++;
                    previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_UP: {
                if (y > 0) {
                    Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    y--;
                    previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_DOWN: {
                if (y < m_playerBoard.getBoardSize() - (horizontal ? 1 : shipSizes[(int)currentShipType])) {
                    Utilities::setShipType(m_playerBoard, x, y, previousShipTypes, horizontal);
                    y++;
                    previousShipTypes = Utilities::getShipTypes(m_playerBoard, x, y, shipSizes[(int)currentShipType], horizontal);
                    Utilities::setShipType(m_playerBoard, x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
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
    ShipType previousShipType = m_guessBoard.getShip(x, y)->getType();
    Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
    bool playerWon = false;
    bool finished = false;
    while (!finished) {
        std::cout << "Other Player's Board" << std::endl;
        m_guessBoard.showBoard();
        std::cout << "Your Board" << std::endl;
        m_playerBoard.showBoard();

        std::cout << std::endl;

        std::cout << "Change/Move Selection: Arrow Keys" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;

        int c = Utilities::getInput();

        switch (c)
        {
        case KEY_LEFT: {
            if (x > 0) {
                m_guessBoard.getShip(x, y)->setType(previousShipType);
                x--;
                Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
            }
        }break;

        case KEY_RIGHT: {
            if (x < m_guessBoard.getBoardSize() - 1) {
                m_guessBoard.getShip(x, y)->setType(previousShipType);
                x++;
                Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
            }
        }break;


        case KEY_UP: {
            if (y > 0) {
                m_guessBoard.getShip(x, y)->setType(previousShipType);
                y--;
                Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
            }
        }break;

        case KEY_DOWN: {
            if (y < m_guessBoard.getBoardSize() - 1) {
                m_guessBoard.getShip(x, y)->setType(previousShipType);
                y++;
                Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
            }
        }break;

        case KEY_ENTER: {
            if (m_guessBoard.getShip(x, y)->getType() != ShipType::Shot) {
                m_aiBoard.hitShip(x, y);
                m_guessBoard.getShip(x, y)->setDamaged(m_aiBoard.getShip(x, y)->getType() != ShipType::Null);
                m_guessBoard.getShip(x, y)->setType(ShipType::Shot);
                Utilities::updateShipSelection(m_guessBoard, previousShipType, x, y);
                m_ai.doTurn();
                if (Utilities::allDestroyed(m_aiBoard) || Utilities::allDestroyed(m_playerBoard)) {
                    finished = true;
                    playerWon = Utilities::allDestroyed(m_aiBoard);
                }
            }
        }break;
        }

        system("cls");
    }

    if (playerWon)
        Utilities::setColor(DARK_GREEN);
    else
        Utilities::setColor(DARK_RED);
    std::cout << (playerWon ? "You Won!" : "AI Won!") << std::endl;
    Utilities::resetColor();
    std::cout << "Your Opponent's Board" << std::endl;
    m_aiBoard.showBoard();
    std::cout << "Your Board" << std::endl;
    m_playerBoard.showBoard();
}

Board& Game::getPlayerBoard() {
    return m_playerBoard;
}

Board& Game::getAIBoard() {
    return m_aiBoard;
}

Board& Game::getGuessBoard()
{
    return m_guessBoard;
}