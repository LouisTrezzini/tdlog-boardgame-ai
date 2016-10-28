#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

/*
 * A random Othello player thats chooses random legal moves
 */
class RandomPlayer : public IPlayer {
public:
    virtual Move getAction(const GameState& gameState, const std::vector<Move>& legalMoves) const;

    virtual ~RandomPlayer();
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
