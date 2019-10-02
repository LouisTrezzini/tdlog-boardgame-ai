#include "PositionEvaluation.h"

double PositionEvaluation::operator()(const GameState& gameState, Color color, double timePassed) const {
    int result = 0;

    for (int i = 0; i < gameState.getBoard().getSize(); i++) {
        for (int j = 0; j < gameState.getBoard().getSize(); j++) {
            if (gameState.getBoard().pieceAt(i, j) == color) {
                result += positionValues[i][j];
            }
        }
    }

    return result;
}

PositionEvaluation::~PositionEvaluation() {

}
