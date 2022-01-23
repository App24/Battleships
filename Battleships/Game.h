#pragma once
#include "Board.h"
#include "AI.h"
#include <vector>

class Game {
public:
	Game();

	void startGame();

	Board& getPlayerBoard();
	Board& getAIBoard();
	Board& getGuessBoard();
private:
	Board m_playerBoard, m_aiBoard, m_guessBoard;
	AI m_ai;

	void setDifficulty();

	void setupBoard();

	void playGame();
};