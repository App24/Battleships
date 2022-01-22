#include <iostream>
#include "Game.h"
#include "Utilities.h"

int main() {
    Utilities::init();
    Utilities::setDifficulty(Difficulty::Easy);

    Game game;
    game.setupBoard();
    return 0;
}