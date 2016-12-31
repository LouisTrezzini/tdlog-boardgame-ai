#ifndef TDLOG_BOARDGAME_AI_ENDGAMEEVALUATION_H
#define TDLOG_BOARDGAME_AI_ENDGAMEEVALUATION_H


#include "IEvaluationFunction.h"
using namespace std;

/*
 * Function that evaluates if the parameter color has won the game or not
 */
class EndGameEvaluation : public IEvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color, double timePassed) const;

    virtual ~EndGameEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_ENDGAMEEVALUATION_H
