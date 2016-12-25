#ifndef TDLOG_BOARDGAME_AI_HUMANPLAYER_H
#define TDLOG_BOARDGAME_AI_HUMANPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

/*
 * A random Othello player thats chooses random legal moves
 */
class HumanPlayer : public IPlayer {
	string type = "human";
public:
	string name = " ";
    virtual Move getAction(const GameState& gameState) const;
    virtual ~HumanPlayer();
};


#endif //TDLOG_BOARDGAME_AI_HUMANPLAYER_H
