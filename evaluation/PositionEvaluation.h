#ifndef TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H


#include "IEvaluationFunction.h"
using namespace std;

const int positionValues[8][8] = {{99, -8, 8, 6, 6, 8, -8, 99},
                          {-8, -24, -4, -3, -3, -4, -24, -8},
                          {8, -4, 7, 4, 4, 7, -4, 8},
                          {6, -3, 4, 0, 0, 4, -3, 6},
                          {6, -3, 4, 0, 0, 4, -3, 6},
                          {8, -4, 7, 4, 4, 7, -4, 8},
                          {-8, -24, -4, -3, -3, -4, -24, -8},
                          {99, -8, 8, 6, 6, 8, -8, 99}};

/*
 * Function that evaluates the total value of the squares you own
 */
class PositionEvaluation : public IEvaluationFunction {
public:
    virtual double operator()(const GameState& gameState, Color color, double timePassed) const;

    virtual ~PositionEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H
