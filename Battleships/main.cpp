#include <iostream>
#include "Game.h"
#include "Utilities.h"

int main() {
    Utilities::init();
    Utilities::setDifficulty(Difficulty::Medium);

    Game game;
    game.startGame();
    return 0;
}