#ifndef TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H
#define TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H

#include <memory>
#include <string>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../game/Node.h"

/*
 * An Othello player thats plays with a Monte Carlo Tree Search
 */
class MonteCarloTreeSearchPlayer : public IPlayer {
    std::unique_ptr<Node> computeTree(const GameState& rootState) const;

public:
    virtual Move getAction(const GameState& gameState) const;

    virtual ~MonteCarloTreeSearchPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H
