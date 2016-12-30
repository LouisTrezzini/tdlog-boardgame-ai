#include "IPlayer.h"
#include "AlphaBetaPlayer.h"

// FIXME Faire quelquechose des constantes

Move IPlayer::getAction(const GameState& gameState) const {
    if(bestFinish && pow(gameState.getBoard().getSize(), 2) - gameState.getBoard().getTotalStones() <= 19) {
        GameState nextGameState = gameState;
        std::shared_ptr<IEvaluationFunction> evalFunction(new EndGameEvaluation());
        cout << "J'ai essayé" << endl;
        MinMaxOutput output = AlphaBetaPlayer::alphaBeta(nextGameState, evalFunction,
                                                         100, true, -1., 1., gameState.getColorPlaying());
        if (output.value == 1) {
            cout << "J'ai gagné" << endl;
            return output.move;
        }
    }
    return getBasicAction(gameState);
}