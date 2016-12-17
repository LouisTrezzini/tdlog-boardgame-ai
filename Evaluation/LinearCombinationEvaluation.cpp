#include "LinearCombinationEvaluation.h"

//FIXME
// Mettre des exceptions pour vois si les tailles sont égales
LinearCombinationEvaluation::LinearCombinationEvaluation(vector<double> coefficients_, vector<EvaluationFunction*> fonctions_){
    coefficients = coefficients_;
    fonctions = fonctions_;
}

double LinearCombinationEvaluation::operator()(const GameState& gameState, Color color) const{
    double result = 0;
    for (int i = 0; i < coefficients.size(); i ++) {
        result += (*fonctions[i])(gameState, color) * coefficients[i];
    }
    return 1;
}

LinearCombinationEvaluation::~LinearCombinationEvaluation() {

}