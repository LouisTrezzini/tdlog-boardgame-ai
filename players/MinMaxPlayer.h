#ifndef TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
#define TDLOG_BOARDGAME_AI_MINMAXPLAYER_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../evaluation/IEvaluationFunction.h"
#include <memory>
#include "../utils/MinMaxOutput.h"
#include <chrono>
#include <future>

/*
 * This IA will follow the minmax principle
 */
class MinMaxPlayer : public IPlayer {
    std::shared_ptr<IEvaluationFunction> evaluationFunction;
    int depth;
public:

    MinMaxPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_, float timeRemainingToPlay_ = 0);


    MinMaxOutput minMax(const GameState& gameState, int depth, bool isMyTurn, Color colorPlaying,
                        std::chrono::time_point<std::chrono::system_clock>  start);

    MinMaxOutput minMaxLength(const GameState& gameState, bool isMyTurn, Color colorPlaying,
                              std::chrono::time_point<std::chrono::system_clock>  start);

    virtual MinMaxOutput minMaxDepth(const GameState& gameState, int depth, bool isMyTurn, Color colorPlaying,
                                     std::chrono::time_point<std::chrono::system_clock>  start) const;

    virtual Move getBasicAction(const GameState& gameState);

    ~MinMaxPlayer();
};


#endif //TDLOG_BOARDGAME_AI_MINMAXPLAYER_H
