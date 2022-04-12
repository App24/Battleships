#pragma once

#include <Windows.h>
#include <conio.h>
#include <random>
#include "Difficulty.h"

// The different color defines used to print color to the console
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
#define GET_BACKGROUND(FOREGROUND, BACKGROUND) ((FOREGROUND)+(BACKGROUND)*16)

#pragma endregion

// Defines for the different keys used in the game
#pragma region KEY_DEFINES

#define KEY_R 114
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESCAPE 27

#pragma endregion

inline HANDLE _hConsole;
inline std::random_device dev;
inline std::mt19937 rng;
inline Difficulty gameDifficulty;

inline void input_init() {
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("Battleships");
	rng = std::mt19937(dev());
}

inline void setColor(WORD wAttributes) {
	SetConsoleTextAttribute(_hConsole, wAttributes);
}

inline void resetColor() {
	setColor(LIGHT_GREY);
}

inline int getInput() {
	return _getch();
}

inline int randomInt(int minValue, int maxValue) {
	std::uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);
	return dist(rng);
}