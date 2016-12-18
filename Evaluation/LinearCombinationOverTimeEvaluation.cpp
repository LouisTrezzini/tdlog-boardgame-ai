#include "LinearCombinationOverTimeEvaluation.h"

//FIXME
// Mettre des exceptions pour vois si les tailles sont égales
LinearCombinationOverTimeEvaluation::LinearCombinationOverTimeEvaluation(const vector<double>& coefficients_,
                                                                         const vector<EvaluationFunction*>& fonctions_){
    coefficients = coefficients_;
    fonctions = fonctions_;
}

double LinearCombinationOverTimeEvaluation::operator()(const GameState& gameState, Color color) const{
    double result = 0;
    int turn = gameState.getBoard().getBlackStones() + gameState.getBoard().getWhiteStones() - InitialStones;
    int totalTurn = pow(gameState.getBoard().getSize(),2) - InitialStones;
    for (int i = 0; i < fonctions.size(); i ++) {
        result += (*fonctions[i])(gameState, color) * coefficients[i * totalTurn + turn];
    }
    return result;
}

LinearCombinationOverTimeEvaluation::~LinearCombinationOverTimeEvaluation() {

}