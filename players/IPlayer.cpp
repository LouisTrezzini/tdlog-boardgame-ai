#include "IPlayer.h"
#include "AlphaBetaPlayer.h"
#include <chrono>
#include <math.h>

// FIXME Faire quelquechose des constantes

Move IPlayer::getAction(const GameState& gameState) {
    if(bestFinish && pow(gameState.getBoard().getSize(), 2) - gameState.getBoard().getTotalStones() <= 19) {
        cout << "L'ordinateur regarde si il peut gagner à coup sûr" << endl;
        if (pow(gameState.getBoard().getSize(), 2) - gameState.getBoard().getTotalStones() <= 10) {
            GameState nextGameState = gameState;
            std::shared_ptr<IEvaluationFunction> evalFunction(new PawnNumberEvaluation());
            // FIXME Il faut allouer un cetain temps à ce joueur, sinon il peut jouer trop longtemps
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
            MinMaxOutput output = AlphaBetaPlayer::alphaBeta(nextGameState, evalFunction,
                                                             100, true, 0, pow(gameState.getBoard().getSize(), 2), gameState.getColorPlaying(), start);
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
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        MinMaxOutput output = AlphaBetaPlayer::alphaBeta(nextGameState, evalFunction,
                                                         100, true, -1., 1., gameState.getColorPlaying(), start);
        if (output.value == 1) {
            cout << "L'ordinateur a gagné à coup sûr" << endl;
            return output.move;
        }
        cout << "Si vous jouez optimalement, vous gagnez" << endl;
    }
    return getBasicAction(gameState);
}

Move IPlayer::getActionStoringTime(const GameState& gameState, std::vector<double> &timeNeededToPlay) {
    auto start = std::chrono::system_clock::now();
    Move moveToPlay = getAction(gameState);
    // TODO Exception si timeNeededToPlay n'est pas initialisé correctement
    // TODO Le -4 est moche
    std::chrono::duration<double> timePassed = std::chrono::system_clock::now() - start;
    timeNeededToPlay[gameState.getBoard().getTotalStones() - 4] += timePassed.count();
    return moveToPlay;
}
