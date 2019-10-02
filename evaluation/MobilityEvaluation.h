#ifndef TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H
#define TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H


#include "IEvaluationFunction.h"

/*
 * Function that evaluates mobility
 */
class MobilityEvaluation : public IEvaluationFunction {

public:
    virtual double operator()(const GameState& gameState, Color color, double timePassed) const;

    virtual ~MobilityEvaluation();
};


#endif //TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H
