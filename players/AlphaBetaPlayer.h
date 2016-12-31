#ifndef TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
#define TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"
#include "../evaluation/IEvaluationFunction.h"
#include <memory>
#include <chrono>

/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
    std::shared_ptr<IEvaluationFunction> evaluationFunction;
    int depth;
public:
    AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_);

    MinMaxOutput alphaBeta(GameState& gameState, int profondeur, bool turn, float alpha, float beta, Color colorPlaying,
                           std::chrono::time_point<std::chrono::system_clock> start) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
