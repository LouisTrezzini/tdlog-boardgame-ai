#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include <string>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"

/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
	std::string type = "iaMinMax";
	std::string name ="MinMaxPlayer";
public:
    std::string getType(){
        return MinMaxPlayer::type;
    }
    std::string getName(){
        return MinMaxPlayer::name;
    }
    MinMaxOutput minMax(GameState& gameState, int profondeur, bool turn) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
