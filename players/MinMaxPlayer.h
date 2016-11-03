#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
public:


    virtual Move getAction(const GameState& gameState) const;

    virtual ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
