#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H

#include <string>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"


/*
 * A random Othello player thats chooses random legal moves
 */
class RandomPlayer : public IPlayer {
	std::string type = "iaRandom";
	std::string name = "RandomPlayer";
public:
    std::string getType(){
        return RandomPlayer::type;
    }
    std::string getName(){
        return RandomPlayer::name;
    }
    virtual Move getAction(const GameState& gameState) const;

    virtual ~RandomPlayer();
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
