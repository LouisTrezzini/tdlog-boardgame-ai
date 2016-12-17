#ifndef TDLOG_BOARDGAME_AI_PAWNNUMBEREVALUATION_H
#define TDLOG_BOARDGAME_AI_PAWNNUMBEREVALUATION_H


#include "../game/Game.h"
#include "EvaluationFunction.h"

/*
 * Function that evaluates the number of pawns of a player
 */
class PawnNumberEvaluation : public EvaluationFunction {

public:
    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~PawnNumberEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_PAWNNUMBEREVALUATION_H
