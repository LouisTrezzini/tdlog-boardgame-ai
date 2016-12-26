#ifndef TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H
#define TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H


#include "IEvaluationFunction.h"
#include <vector>

using namespace std;

const int InitialStones = 4;

/*
 * Combination of evaluation functions over time
 */
class LinearCombinationOverTimeEvaluation : public IEvaluationFunction {
private:
    vector<double> coefficients;
    vector<IEvaluationFunction *> functions;
public:

    LinearCombinationOverTimeEvaluation(const vector<double>& coefficients,
                                        const vector<IEvaluationFunction *>& functions);

    virtual double operator()(const GameState& gameState, Color color) const;

    virtual ~LinearCombinationOverTimeEvaluation();
};


#endif //TDLOG_BOARDGAME_AI_LINEARCOMBINATIONEVALUATIONOVERTIME_H