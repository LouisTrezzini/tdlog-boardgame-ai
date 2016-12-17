#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H


#include "EvaluationFunction.h"
#include <vector>
using namespace std;

/*
 * Combination of evaluation functions
 */
class LinearCombinationEvaluation : public EvaluationFunction {
private:
    vector<double> coefficients;
    vector<EvaluationFunction*> fonctions;
public:

    LinearCombinationEvaluation(vector<double> coefficients_, vector<EvaluationFunction*> fonctions_);

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~LinearCombinationEvaluation();
};



#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
