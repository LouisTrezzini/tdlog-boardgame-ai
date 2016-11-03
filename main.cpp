#include <iostream>
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "game/Game.h"

int main() {
    HumanPlayer whitePlayer;
    MonteCarloTreeSearchPlayer blackPlayer;

    Game game(8, &whitePlayer, &blackPlayer);

    game.playGame();

    std::cout << game.getWinner(game.getGameState()) << std::endl;

    return 0;
}
