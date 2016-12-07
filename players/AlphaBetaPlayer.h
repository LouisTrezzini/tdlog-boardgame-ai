#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

const float INF = 1 / 0.f;
const int profondeur = 7;


/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
public:

    virtual Move getAction(const GameState& gameState) const;

    virtual ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
