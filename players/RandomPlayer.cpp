#include <random>
#include "RandomPlayer.h"


Move RandomPlayer::getAction(const GameState& gameState, const std::vector<Move>& legalMoves) const {
    if (legalMoves.size() > 0){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, legalMoves.size() - 1);

        return legalMoves[distrib(gen)];
    }

    return Move::passing();
}

RandomPlayer::~RandomPlayer() {

}




