#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H


#include "IEvaluationFunction.h"
#include <vector>
#include <memory>

using namespace std;

/*
 * Combination of evaluation functions
 */
class LinearCombinationEvaluation : public IEvaluationFunction {
private:
    vector<double> coefficients;
    vector<std::shared_ptr<IEvaluationFunction>> functions;
public:

    LinearCombinationEvaluation(vector<double> coefficients, vector<std::shared_ptr<IEvaluationFunction>> functions);

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~LinearCombinationEvaluation();
};


#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATION_H
