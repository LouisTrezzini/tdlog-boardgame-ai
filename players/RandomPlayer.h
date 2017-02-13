#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H


#include <cstdlib>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"


/*
 * A random Othello player thats chooses random legal moves
 */
class RandomPlayer : public IPlayer {
public:
    RandomPlayer(float timeRemainingToPlay_ = 0) {
        srand(time(NULL));
        setTimeRemainingToPlay( timeRemainingToPlay_);
    }

    virtual Move getAction(const GameState& gameState);

    virtual ~RandomPlayer();
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
