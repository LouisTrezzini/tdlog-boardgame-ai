#include <random>
#include "RandomPlayer.h"
#include "../game/Game.h"

std::mt19937 RandomPlayer::generator;

RandomPlayer::RandomPlayer() {
    RandomPlayer::generator = std::mt19937(time(NULL));
}

Move RandomPlayer::getAction(const GameState& gameState) const{
    std::vector<Move> legalMoves = Game::getLegalMoves(gameState);
    std::uniform_int_distribution<int> distrib(0, int(legalMoves.size() - 1));
    int moveChosen = distrib(RandomPlayer::generator);
    return legalMoves[moveChosen];
}

RandomPlayer::~RandomPlayer() {

}

void RandomPlayer::seedGenerator(int seed) {
    RandomPlayer::generator.seed(seed);
}




