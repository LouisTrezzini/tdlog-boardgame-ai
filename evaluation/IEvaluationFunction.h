#ifndef TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H


#include "../game/Game.h"

/*
 * Abstract for all evaluation function
 */
class IEvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color) const = 0;

    virtual ~IEvaluationFunction() = 0;
};

inline IEvaluationFunction::~IEvaluationFunction() {};


#endif //TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
