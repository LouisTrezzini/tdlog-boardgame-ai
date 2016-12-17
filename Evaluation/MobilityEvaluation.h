#ifndef TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H
#define TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H


#include "../game/Game.h"
#include "EvaluationFunction.h"

/*
 * Function that evaluates mobility
 */
class MobilityEvaluation : public EvaluationFunction {

public:
    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~MobilityEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_MOBILITYEVALUATION_H
