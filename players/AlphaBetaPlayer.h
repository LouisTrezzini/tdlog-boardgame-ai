#ifndef TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
#define TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"
#include "../evaluation/IEvaluationFunction.h"
#include <memory>


/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
    std::shared_ptr<IEvaluationFunction> evaluationFunction;
    int depth;
public:

    AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_);

    static MinMaxOutput alphaBeta(GameState& gameState,
                                  const std::shared_ptr<IEvaluationFunction> &evalFunction,
                                  int profondeur, bool turn, double alpha, double beta,
                                  const Color &colorPlaying);

    virtual Move getBasicAction(const GameState& gameState) const;

    virtual ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
