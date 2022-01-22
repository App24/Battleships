#pragma once
#include <windows.h>

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
private:
	static HANDLE hConsole;
};