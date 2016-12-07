#include "../game/Game.h"
#include "AlphaBetaPlayer.h"


Move AlphaBetaPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

AlphaBetaPlayer::~AlphaBetaPlayer() {

}



