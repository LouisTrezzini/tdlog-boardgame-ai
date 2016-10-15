#include <iostream>
#include "players/RandomPlayer.h"
#include "game/Game.h"

int main() {
    RandomPlayer whitePlayer(Color::WHITE);
    RandomPlayer blackPlayer(Color::BLACK);

    Game game(8, &whitePlayer, &blackPlayer);

    game.playGame();

    std::cout << game.getWinner(game.getGameState()) << std::endl;

    return 0;
}
