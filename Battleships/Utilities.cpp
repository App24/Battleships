#include "Utilities.h"
#include <conio.h>

HANDLE Utilities::hConsole;
Difficulty Utilities::m_difficulty;

void Utilities::init() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Utilities::setColor(WORD wAttributes) {
	SetConsoleTextAttribute(hConsole, wAttributes);
}

void Utilities::resetColor() {
	setColor(LIGHT_GREY);
}

int Utilities::getInput() {
	return _getch();
}


Difficulty Utilities::getDifficulty() {
	return m_difficulty;
}

void Utilities::setDifficulty(Difficulty difficulty) {
	m_difficulty = difficulty;
}