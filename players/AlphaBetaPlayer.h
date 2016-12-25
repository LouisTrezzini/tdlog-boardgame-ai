#ifndef TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
#define TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H

#include <string>
#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"


/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
	std::string type = "iaAlphaBeta";
	std::string name = "AlphaBetaPlayer";
public:
    std::string getType(){
        return AlphaBetaPlayer::type;
    }
    std::string getName(){
        return AlphaBetaPlayer::name;
    }
    MinMaxOutput alphaBeta(GameState& gameState, int profondeur, bool turn, float alpha, float beta) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
