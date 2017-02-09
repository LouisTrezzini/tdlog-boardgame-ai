#include "LinearCombinationEvaluation.h"

//FIXME
// Mettre des exceptions pour vois si les tailles sont égales
LinearCombinationEvaluation::LinearCombinationEvaluation(vector<double> coefficients,
                                                         vector<std::shared_ptr<IEvaluationFunction>> functions)
        : coefficients(coefficients), functions(functions) {
}

double LinearCombinationEvaluation::operator()(const GameState& gameState, Color color) const {
    double result = 0;

    for (int i = 0; i < coefficients.size(); i++) {
        result += (*functions[i])(gameState, color) * coefficients[i];
    }

    return result;
}

LinearCombinationEvaluation::~LinearCombinationEvaluation() {

}