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

    HumanPlayer(float timeRemainingToPlay_= 0){
        setTimeRemainingToPlay(timeRemainingToPlay_);
        bestFinish = false;
    }

    HumanPlayer(const std::string& name, float timeRemainingToPlay_= 0) {
        this->name = name;
        setTimeRemainingToPlay(timeRemainingToPlay_);
        bestFinish = false;
    }

    virtual Move getBasicAction(const GameState& gameState);


    std::string getName() const{
        return name;
    }

    virtual bool isHuman() {
        return true;
    }

    virtual ~HumanPlayer();
};


#endif //TDLOG_BOARDGAME_AI_HUMANPLAYER_H
