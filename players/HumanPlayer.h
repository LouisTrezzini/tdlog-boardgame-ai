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
	std::string type = "HumanPlayer";
	std::string name;

public:
    std::string getType(){
        return HumanPlayer::type;
    }
    std::string getName(){
        return HumanPlayer::name;
    }
    void setName(std::string Name){
        HumanPlayer::name=Name;
    }

    virtual Move getAction(const GameState& gameState) const;
    virtual ~HumanPlayer();
};


#endif //TDLOG_BOARDGAME_AI_HUMANPLAYER_H
