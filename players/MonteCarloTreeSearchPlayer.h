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
	std::string type = "iaMonteCarlo";
	std::string name = "MonteCarloTreeSearchPlayer";
    std::unique_ptr<Node> computeTree(const GameState& rootState) const;

public:
    std::string getType(){
        return MonteCarloTreeSearchPlayer::type;
    }
    std::string getName(){
        return MonteCarloTreeSearchPlayer::name;
    }
    virtual Move getAction(const GameState& gameState) const;

    virtual ~MonteCarloTreeSearchPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MONTECARLOTREESEARCHPLAYER_H
