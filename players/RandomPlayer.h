#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H


#include <string>
#include <cstdlib>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"


/*
 * A random Othello player thats chooses random legal moves
 */
class RandomPlayer : public IPlayer {
public:
    RandomPlayer() {
        srand(time(NULL));
    }

    virtual Move getAction(const GameState& gameState) const;

    virtual ~RandomPlayer();
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
