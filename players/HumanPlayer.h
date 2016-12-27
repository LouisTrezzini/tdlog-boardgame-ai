#ifndef TDLOG_BOARDGAME_AI_HUMANPLAYER_H
#define TDLOG_BOARDGAME_AI_HUMANPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include <string>

/*
 * A random Othello player thats chooses random legal moves
 */
class HumanPlayer : public IPlayer {
	std::string name;

public:
    HumanPlayer(std::string name_) {
        name = name_;
    }

    std::string getName(){
        return name;
    }

    virtual bool isHuman() {
        return true;
    }

    virtual Move getAction(const GameState& gameState) const;
    virtual ~HumanPlayer();
};


#endif //TDLOG_BOARDGAME_AI_HUMANPLAYER_H
