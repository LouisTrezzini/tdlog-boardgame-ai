#include "../game/Game.h"
#include "AlphaBetaPlayer.h"

const float INF = 1 / 0.f;

AlphaBetaPlayer::AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_) {
    evaluationFunction = eval;
    depth = depth_;
}

MinMaxOutput AlphaBetaPlayer::alphaBeta(GameState& gameState, int profondeur, bool isMyTurn, float alpha, float beta, Color colorPlaying) const {
    if (gameState.getBoard().isFull() || profondeur <= 0) {
        return MinMaxOutput(Move::passing(), (*evaluationFunction)(gameState, colorPlaying));
    }
    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = alphaBeta(nextGameState, profondeur - 1, false, alpha, beta, colorPlaying);
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
                MinMaxOutput moveResult = alphaBeta(nextGameState, profondeur - 1, true, alpha, beta, colorPlaying);
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

Move AlphaBetaPlayer::getAction(const GameState& gameState) const {
    GameState nextGameState = gameState;
    MinMaxOutput resultat = alphaBeta(nextGameState, depth, true, - INF, INF, gameState.getColorPlaying());
    return resultat.move;
}

AlphaBetaPlayer::~AlphaBetaPlayer() {

}



