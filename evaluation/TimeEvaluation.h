#ifndef TDLOG_BOARDGAME_AI_TIMEEVALUATION_H
#define TDLOG_BOARDGAME_AI_TIMEEVALUATION_H

#include <chrono>
#include "IEvaluationFunction.h"
using namespace std;

class TimeEvaluation : public IEvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color, double timePassed) const;

    virtual ~TimeEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_TIMEEVALUATION_H
