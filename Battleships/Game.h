#pragma once
#include "Board.h"
#include "AI.h"
#include <vector>

class Game {
public:
	Game();

	void setupBoard();

	void playGame();

	Board& getPlayerBoard();
	Board& getAIBoard();
	Board& getGuessBoard();
private:
	Board m_playerBoard, m_aiBoard, m_guessBoard;
	AI m_ai;

	void setShipType(Board& board, unsigned int x, unsigned int y, ShipType shipType, unsigned int shipSize, bool horizontal);
	void setShipType(Board& board, unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal);

	std::vector<ShipType> getShipTypes(Board& board, unsigned int x, unsigned int y, unsigned int shipSize, bool horizontal);

	bool anyOverlay(Board& board);

	void updateShipSelection(Board& board, ShipType& previousShipType, unsigned int x, unsigned int y);
};