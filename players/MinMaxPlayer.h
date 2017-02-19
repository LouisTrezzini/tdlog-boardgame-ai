#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../evaluation/IEvaluationFunction.h"
#include <memory>
#include "../utils/MinMaxOutput.h"
#include <future>

/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
    std::shared_ptr<IEvaluationFunction> evaluationFunction;
    int depth;
public:
    MinMaxPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_);

    virtual MinMaxOutput minMax(const GameState& gameState, int profondeur, bool turn, Color color) const;

    virtual Move getBasicAction(const GameState& gameState) const;

    ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
