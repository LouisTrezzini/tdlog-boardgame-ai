#ifndef TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H


#include "../game/Game.h"
#include <memory>

/*
 * Abstract for all evaluation function
 */
class EvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color) const = 0;

    virtual ~EvaluationFunction() = 0;
};

inline EvaluationFunction::~EvaluationFunction() { };


#endif //TDLOG_BOARDGAME_AI_FONCTIONEVALUATION_H
