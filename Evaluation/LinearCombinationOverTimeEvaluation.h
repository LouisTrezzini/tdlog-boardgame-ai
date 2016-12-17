#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H


#include "EvaluationFunction.h"
#include <vector>
#include <math.h>

using namespace std;

const int InitialStones = 4;

/*
 * Combination of evaluation functions over time
 */
class LinearCombinationOverTimeEvaluation : public EvaluationFunction {
private:
    vector<double> coefficients;
    vector<EvaluationFunction*> fonctions;
public:

    LinearCombinationOverTimeEvaluation(vector<double> coefficients_, vector<EvaluationFunction*> fonctions_);

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~LinearCombinationOverTimeEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H
