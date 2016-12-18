#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H


#include "IEvaluationFunction.h"
#include <vector>

using namespace std;

/*
 * Combination of evaluation functions
 */
class LinearCombinationEvaluation : public IEvaluationFunction {
private:
    vector<double> coefficients;
    vector<IEvaluationFunction *> functions;
public:

    LinearCombinationEvaluation(vector<double> coefficients, vector<IEvaluationFunction *> functions);

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~LinearCombinationEvaluation();
};


#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
