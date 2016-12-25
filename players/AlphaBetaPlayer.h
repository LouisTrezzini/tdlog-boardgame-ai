#ifndef TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
#define TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"


/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
	string type = "iaAlphaBeta";
	string name = "AlphaBetaPlayer";
public:
    MinMaxOutput alphaBeta(GameState& gameState, int profondeur, bool turn, float alpha, float beta) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
