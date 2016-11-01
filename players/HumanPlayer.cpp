#include "HumanPlayer.h"
#include "../game/Game.h"


Move HumanPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

HumanPlayer::~HumanPlayer() {

}




