#include "IPlayer.h"
#include "AlphaBetaPlayer.h"

// FIXME Faire quelquechose des constantes

Move IPlayer::getAction(const GameState& gameState) const {
    if(bestFinish && pow(gameState.getBoard().getSize(), 2) - gameState.getBoard().getTotalStones() <= 19) {
        cout << "L'ordinateur regarde si il peut gagner à coup sûr" << endl;
        if (pow(gameState.getBoard().getSize(), 2) - gameState.getBoard().getTotalStones() <= 12) {
            GameState nextGameState = gameState;
            std::shared_ptr<IEvaluationFunction> evalFunction(new PawnNumberEvaluation());
            // FIXME Il faut allouer un cetain temps à ce joueur, sinon il peut jouer trop longtemps
            MinMaxOutput output = AlphaBetaPlayer::alphaBeta(nextGameState, evalFunction,
                                                             100, true, 0, pow(gameState.getBoard().getSize(), 2), gameState.getColorPlaying());
            if (output.value > pow(gameState.getBoard().getSize(), 2) / 2) {
                cout << "L'ordinateur a gagné à coup sûr avec au moins " << output.value << " pions" << endl;
                return output.move;
            }
            else {
                cout << "Si vous jouez optimalement, vous gagnez. L'ordinateur peut obtienir au moins "
                     << output.value << " pions, mais il ne cherchera pas forcément à"
                     << " maximiser son nombre de pions" << endl;
            }
            return getBasicAction(gameState);
        }
        GameState nextGameState = gameState;
        std::shared_ptr<IEvaluationFunction> evalFunction(new EndGameEvaluation());
        // FIXME Il faut allouer un cetain temps à ce joueur, sinon il peut jouer trop longtemps
        MinMaxOutput output = AlphaBetaPlayer::alphaBeta(nextGameState, evalFunction,
                                                         100, true, -1., 1., gameState.getColorPlaying());
        if (output.value == 1) {
            cout << "L'ordinateur a gagné à coup sûr" << endl;
            return output.move;
        }
        cout << "Si vous jouez optimalement, vous gagnez" << endl;
    }
    return getBasicAction(gameState);
}