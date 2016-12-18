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
    //FIXME
    PositionEvaluation() {
        valueOfCases.push_back({99, -8, 8, 6, 6, 8, -8, 99});
        valueOfCases.push_back({-8, -24, -4, -3, -3, -4, -24, -8});
        valueOfCases.push_back({8, -4, 7, 4, 4, 7, -4, 8});
        valueOfCases.push_back({6, -3, 4, 0, 0, 4, -3, 6});
        valueOfCases.push_back(valueOfCases[3]);
        valueOfCases.push_back(valueOfCases[2]);
        valueOfCases.push_back(valueOfCases[1]);
        valueOfCases.push_back(valueOfCases[0]);
    }

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~PositionEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_POSITIONEVALUATION_H
