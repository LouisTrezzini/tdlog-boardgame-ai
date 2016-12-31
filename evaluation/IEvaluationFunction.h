#ifndef TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H

#include "../game/GameState.h"
#include "../game/Color.h"

const int InitialStones = 4;

/*
 * Abstract for all evaluation function
 */
class IEvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color, double timePassed) const = 0;

    virtual ~IEvaluationFunction() = 0;
};

inline IEvaluationFunction::~IEvaluationFunction() {};


#endif //TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
