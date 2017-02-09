#include "LinearCombinationOverTimeEvaluation.h"
#include <cmath>

//FIXME
// Mettre des exceptions pour vois si les tailles sont égales
LinearCombinationOverTimeEvaluation::LinearCombinationOverTimeEvaluation(const vector<double>& coefficients,
                                                                         const vector<std::shared_ptr<IEvaluationFunction>>& functions) {
    this->coefficients = coefficients;
    this->functions = functions;
}

double LinearCombinationOverTimeEvaluation::operator()(const GameState& gameState, Color color) const {
    double result = 0;
    int turn = gameState.getBoard().getBlackStones() + gameState.getBoard().getWhiteStones() - InitialStones;
    int totalTurn = pow(gameState.getBoard().getSize(), 2) - InitialStones;
    for (int i = 0; i < functions.size(); i++) {
        result += (*functions[i])(gameState, color) * coefficients[i * totalTurn + turn];
    }
    return result;
}

LinearCombinationOverTimeEvaluation::~LinearCombinationOverTimeEvaluation() {

}