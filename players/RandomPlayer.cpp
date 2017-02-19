#include <random>
#include "RandomPlayer.h"
#include "../game/Game.h"
#include <chrono>


std::mt19937 RandomPlayer::generator;

RandomPlayer::RandomPlayer(bool bestFinish, float timeRemainingToPlay_) {
    setTimeRemainingToPlay(timeRemainingToPlay_);
    RandomPlayer::generator = std::mt19937(time(NULL));
    this->bestFinish = bestFinish;
}

Move RandomPlayer::getBasicAction(const GameState& gameState) {
    auto startTime = std::chrono::system_clock::now();
    std::vector<Move> legalMoves = Game::getLegalMoves(gameState);
    std::uniform_int_distribution<int> distrib(0, int(legalMoves.size() - 1));
    int moveChosen = distrib(RandomPlayer::generator);
    double timePassed = (std::chrono::system_clock::now() - startTime).count()/std::chrono::milliseconds::period::den;
    setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
    return legalMoves[moveChosen];   
}

RandomPlayer::~RandomPlayer() {

}

void RandomPlayer::seedGenerator(int seed) {
    RandomPlayer::generator.seed(seed);
}




