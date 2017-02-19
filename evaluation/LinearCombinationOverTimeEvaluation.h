#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H


#include "IEvaluationFunction.h"
#include <vector>
#include <memory>

using namespace std;


/*
 * Combination of evaluation functions over time
 */
class LinearCombinationOverTimeEvaluation : public IEvaluationFunction {
private:
    vector<double> coefficients;
    vector<std::shared_ptr<IEvaluationFunction>> functions;
public:

    LinearCombinationOverTimeEvaluation(const vector<double>& coefficients,
                                        const vector<std::shared_ptr<IEvaluationFunction>>& functions);

    virtual double operator()(const GameState& gameState, Color color, double timePassed) const;

    virtual ~LinearCombinationOverTimeEvaluation();
};


#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H
