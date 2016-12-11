#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

const float INF = 1 / 0.f;
const int profondeur = 7;

// Structure for outputing the right thing
struct MinMaxOutput {
    Move move;
    float value;

    MinMaxOutput(Move move, float value);
    virtual void max(const MinMaxOutput &other);
    virtual void min(const MinMaxOutput &other);
};


/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
public:
    virtual MinMaxOutput minMax(GameState& gameState, int profondeur, bool turn) const;

    virtual Move getAction(const GameState& gameState) const;

    ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
