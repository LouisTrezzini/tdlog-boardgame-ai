#ifndef TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H
#define TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H

#include <memory>

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

    MonteCarloTreeSearchPlayer (float timeRemainingToPlay_ = 0){
        setTimeRemainingToPlay(timeRemainingToPlay_);
    }

    virtual Move getAction(const GameState& gameState);

    virtual ~MonteCarloTreeSearchPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H
