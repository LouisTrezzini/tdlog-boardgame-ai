#ifndef TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H


#include "../game/Game.h"
#include "EvaluationFunction.h"
#include "vector"
using namespace std;

/*
 * Function that evaluates the total value of the squares you own
 */
class PositionEvaluation : public EvaluationFunction {
    vector<vector<int>> valueOfCases;
public:
    PositionEvaluation() {
        valueOfCases[0] = {99, -8, 8, 6, 6, 8, -8, 99};
        valueOfCases[1] = {-8, -24, -4, -3, -3, -4, -24, -8};
        valueOfCases[2] = {8, -4, 7, 4, 4, 7, -4, 8};
        valueOfCases[3] = {6, -3, 4, 0, 0, 4, -3, 6};
        valueOfCases[4] = valueOfCases[3];
        valueOfCases[5] = valueOfCases[2];
        valueOfCases[6] = valueOfCases[1];
        valueOfCases[7] = valueOfCases[0];
    }

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~PositionEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H
