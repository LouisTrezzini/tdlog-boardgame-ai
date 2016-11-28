#include <iostream>
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "game/Game.h"

int main(int argc, char *argv[]) {
    RandomPlayer whitePlayer;
    HumanPlayer blackPlayer;

    Game game(8, &whitePlayer, &blackPlayer);

    game.playGame();

    std::cout << game.getWinner(game.getGameState()) << std::endl;

    return 0;
}
