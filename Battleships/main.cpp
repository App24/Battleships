#include <iostream>
#include "Game.h"
#include "Utilities.h"

int main() {
    Utilities::init();

    Game game;
    game.setupBoard();
    return 0;
}