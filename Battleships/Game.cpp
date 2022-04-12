#include "Game.h"

#include "Utils.h"
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
        setColor(colors[currentDifficultyInt]);
        std::cout << difficultyString[currentDifficultyInt] << std::endl;
        resetColor();

        std::cout << std::endl;

        std::cout << "Change Selection: Arrow Keys" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;

        int c = getInput();

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
            gameDifficulty = currentDifficulty;
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

    int remainingShips[] = {0, 1, 1, 1, 1, 1};

    bool horizontal = true;

    bool finished = false;

    while (!finished) {
        if (remainingShips[(int)currentShipType] <= 0) {
            setColor(DARK_RED);
        }
        else if (selectMode) {
            setColor(GREEN);
        }
        std::cout << shipTypeString[(int)currentShipType] << std::endl;

        setColor(DARK_CYAN);
        std::cout << (char)(65 + x) << " ";

        setColor(DARK_YELLOW);
        std::cout << (y + 1) << std::endl;

        resetColor();

        m_playerBoard.show();

        std::cout << std::endl;

        std::cout << "Change/Move Selection: Arrow Keys" << std::endl;
        std::cout << "Rotate: R Key" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;
        std::cout << "Go Back/Finish: Escape Key" << std::endl;

        int c = getInput();

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
                    previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
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
                m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
                horizontal = !horizontal;
                if (horizontal && x >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    x = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                else if (!horizontal && y >= m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType]) {
                    y = m_playerBoard.getBoardSize() - shipSizes[(int)currentShipType];
                }
                previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
            }break;

            case KEY_ESCAPE: {
                selectMode = true;
                m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
            }break;

            case KEY_ENTER: {
                if (!m_playerBoard.anyOverlap()) {
                    remainingShips[(int)currentShipType]--;
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                    x = 0;
                    y = 0;
                    selectMode = true;
                }
            }break;

            case KEY_LEFT: {
                if (x > 0) {
                    m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
                    x--;
                    previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_RIGHT: {
                if (x < m_playerBoard.getBoardSize() - (horizontal ? shipSizes[(int)currentShipType] : 1)) {
                    m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
                    x++;
                    previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_UP: {
                if (y > 0) {
                    m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
                    y--;
                    previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
                }
            }break;

            case KEY_DOWN: {
                if (y < m_playerBoard.getBoardSize() - (horizontal ? 1 : shipSizes[(int)currentShipType])) {
                    m_playerBoard.setShipTypes(x, y, previousShipTypes, horizontal);
                    y++;
                    previousShipTypes = m_playerBoard.getShipTypes(x, y, shipSizes[(int)currentShipType], horizontal);
                    m_playerBoard.setShipType(x, y, currentShipType, shipSizes[(int)currentShipType], horizontal);
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

    ShipType previousShipType = m_guessBoard.getShip(x, y).shipType;

    m_guessBoard.updateShipSelection(previousShipType, x, y);

    bool playerWon = false;

    bool finished = false;

    while (!finished) {
        std::cout << "Other Player's Board" << std::endl;
        m_guessBoard.show();
        std::cout << "Your Board" << std::endl;
        m_aiBoard.show();

        std::cout << std::endl;

        std::cout << "Change/Move Selection: Arrow Keys" << std::endl;
        std::cout << "Confirm Selection: Enter Key" << std::endl;

        int c = getInput();

        switch (c)
        {
        case KEY_LEFT: {
            if (x > 0) {
                m_guessBoard.getShip(x, y).shipType= previousShipType;
                x--;
                m_guessBoard.updateShipSelection(previousShipType, x, y);
            }
        }break;

        case KEY_RIGHT: {
            if (x < m_guessBoard.getBoardSize() - 1) {
                m_guessBoard.getShip(x, y).shipType= previousShipType;
                x++;
                m_guessBoard.updateShipSelection(previousShipType, x, y);
            }
        }break;


        case KEY_UP: {
            if (y > 0) {
                m_guessBoard.getShip(x, y).shipType= previousShipType;
                y--;
                m_guessBoard.updateShipSelection(previousShipType, x, y);
            }
        }break;

        case KEY_DOWN: {
            if (y < m_guessBoard.getBoardSize() - 1) {
                m_guessBoard.getShip(x, y).shipType= previousShipType;
                y++;
                m_guessBoard.updateShipSelection(previousShipType, x, y);
            }
        }break;

        case KEY_ENTER: {
            if (previousShipType != ShipType::Shot) {
                m_aiBoard.hitShip(x, y);
                m_guessBoard.getShip(x, y).damaged=m_aiBoard.getShip(x, y).shipType != ShipType::Empty;
                m_guessBoard.getShip(x, y).shipType=ShipType::Shot;
                m_guessBoard.updateShipSelection(previousShipType, x, y);
                m_ai.doTurn();
                if (m_aiBoard.allDestroyed() || m_playerBoard.allDestroyed()) {
                    finished = true;
                    playerWon = m_aiBoard.allDestroyed();
                }
            }
        }break;
        }

        system("cls");
    }

    if (playerWon)
        setColor(DARK_GREEN);
    else
        setColor(DARK_RED);
    std::cout << (playerWon ? "You Won!" : "AI Won!") << std::endl;
    resetColor();
    std::cout << "Your Opponent's Board" << std::endl;
    m_aiBoard.show();
    std::cout << "Your Board" << std::endl;
    m_playerBoard.show();

    system("pause");
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