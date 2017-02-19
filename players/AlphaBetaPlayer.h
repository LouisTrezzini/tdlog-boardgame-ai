#ifndef TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
#define TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../utils/MinMaxOutput.h"
#include "../evaluation/IEvaluationFunction.h"
#include <memory>
#include <chrono>
#include <thread>
#include <future>



/*
 * This IA will follow the alpha-beta principle
 */
class AlphaBetaPlayer : public IPlayer {
    std::shared_ptr<IEvaluationFunction> evaluationFunction;
    int depth;
public:

    AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_, float timeRemainingToPlay_ = 0);

    static MinMaxOutput alphaBeta(const GameState& gameState,
                                  const std::shared_ptr<IEvaluationFunction> &evalFunction,
                                  int profondeur, bool turn, double alpha, double beta,
                                  const Color &colorPlaying,
                                  std::chrono::time_point<std::chrono::system_clock> start);

    virtual Move getBasicAction(const GameState& gameState);

    ~AlphaBetaPlayer();
};


#endif //TDLOG_BOARDGAME_AI_ALPHABETAPLAYER_H
