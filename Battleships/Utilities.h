#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "Board.h"
#include "Difficulty.h"

#pragma region COLOR_DEFINES

#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_CYAN 3
#define DARK_RED 4
#define DARK_MAGENTA 5
#define DARK_YELLOW 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BACKGROUND_COLOR 16
#define GET_BACKGROUND(f, b) (f+b*BACKGROUND_COLOR)

#pragma endregion

#pragma region KEY_DEFINES

#define KEY_R 114
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESCAPE 27

#pragma endregion

class Utilities {
public:
	static void init();

	static void setColor(WORD wAttributes);
	static void resetColor();

	static int getInput();

	static Difficulty getDifficulty();
	static void setDifficulty(Difficulty difficulty);

	static void setShipType(Board& board, unsigned int x, unsigned int y, ShipType shipType, unsigned int shipSize, bool horizontal);
	static void setShipType(Board& board, unsigned int x, unsigned int y, std::vector<ShipType> shipTypes, bool horizontal);

	static std::vector<ShipType> getShipTypes(Board& board, unsigned int x, unsigned int y, unsigned int shipSize, bool horizontal);

	static void updateShipSelection(Board& board, ShipType& previousShipType, unsigned int x, unsigned int y);

	static bool anyOverlay(Board& board);

	static bool allDestroyed(Board& board);

	static std::string getStrPos(unsigned int x, unsigned int y);
private:
	static HANDLE hConsole;
	static Difficulty m_difficulty;
};