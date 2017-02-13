#include <random>
#include "RandomPlayer.h"
#include "../game/Game.h"
#include <chrono>

Move RandomPlayer::getAction(const GameState& gameState) {
    auto startTime = std::chrono::system_clock::now();
    double timePassed = (std::chrono::system_clock::now() - startTime).count()/std::chrono::milliseconds::period::den;
    setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
    return Game::getRandomMove(gameState);
}

RandomPlayer::~RandomPlayer() {

}




