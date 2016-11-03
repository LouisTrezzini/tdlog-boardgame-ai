#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

float INF = 1 / 0.f;

// Structure for outputing the right thing
struct MinMaxOutput {
    Move move;
    float value;

    MinMaxOutput(Move move, float value);
    void max(const MinMaxOutput &other);
    void min(const MinMaxOutput &other);
};


/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
public:
    MinMaxOutput minMax(GameState& gameState, int profondeur, bool turn) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
