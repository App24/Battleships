#pragma once
#include "Board.h"
#include "AI.h"
#include <vector>

class Game {
public:
	Game();

	// The main function to be called to start the game
	void startGame();

	Board& getPlayerBoard();
	Board& getAIBoard();
	Board& getGuessBoard();
private:
	Board m_playerBoard, m_aiBoard, m_guessBoard;
	AI m_ai;

	// First step of starting a game, setting the difficulty
	void setDifficulty();

	// Allow for the user to place the different ships around on their board
	void setupBoard();

	// Play the game, starting with the player's turn
	void playGame();
};