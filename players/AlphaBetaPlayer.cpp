#include "../game/Game.h"
#include "AlphaBetaPlayer.h"

const double INF = 1 / 0.f;

AlphaBetaPlayer::AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_) {
    evaluationFunction = eval;
    depth = depth_;
    bestFinish = bestFinish_;
}

MinMaxOutput AlphaBetaPlayer::alphaBeta(GameState& gameState,
                                        const std::shared_ptr<IEvaluationFunction> &evalFunction,
                                        int profondeur, bool isMyTurn, double alpha, double beta,
                                        const Color &colorPlaying) {
    if (gameState.getBoard().isFull() || profondeur <= 0) {
        return MinMaxOutput(Move::passing(), (*evalFunction)(gameState, colorPlaying));
    }
    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = alphaBeta(nextGameState, evalFunction, profondeur - 1,
                                                    false, alpha, beta, colorPlaying);
                moveResult.move = moves[i];
                bestResult.max(moveResult);
                if (bestResult.value >= beta) {
                    return bestResult;
                }
                alpha = std::max(alpha, bestResult.value);
            }
            return bestResult;
        }
        else {
            MinMaxOutput bestResult(Move::passing(), INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = alphaBeta(nextGameState, evalFunction,
                                                    profondeur - 1, true, alpha, beta, colorPlaying);
                moveResult.move = moves[i];
                bestResult.min(moveResult);
                if (bestResult.value <= alpha) {
                    return bestResult;
                }
                beta = std::min(beta, bestResult.value);
            }
            return bestResult;
        }
    }
}

Move AlphaBetaPlayer::getBasicAction(const GameState& gameState) const {
    GameState nextGameState = gameState;
    MinMaxOutput resultat = AlphaBetaPlayer::alphaBeta(nextGameState, evaluationFunction, depth,
                                      true, - INF, INF, gameState.getColorPlaying());
    return resultat.move;
}

AlphaBetaPlayer::~AlphaBetaPlayer() {

}



