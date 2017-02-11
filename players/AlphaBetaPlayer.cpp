#include "../game/Game.h"
#include "AlphaBetaPlayer.h"

const float INF = 1 / 0.f;

AlphaBetaPlayer::AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth) {
    this->evaluationFunction = eval;
    this->depth = depth;
}

MinMaxOutput AlphaBetaPlayer::alphaBeta(const GameState& gameState, int profondeur, bool isMyTurn, float alpha, float beta, Color colorPlaying) const {
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
    // Sans parallélisation
    if (false) {
        GameState nextGameState = gameState;
        MinMaxOutput resultat = alphaBeta(nextGameState, depth, true, -INF, INF, gameState.getColorPlaying());
        return resultat.move;
    // Avec parallélisation
    } else {
        Color colorPlaying = gameState.getColorPlaying();
        auto moves = Game::getLegalMoves(gameState);
        std::vector<std::future<double>> branchResults;

        for  (int i = 0; i < moves.size(); i ++) {
            GameState nextGameState = gameState;
            Game::applyMove(nextGameState, moves[i]);

            branchResults.push_back(std::async(std::launch::async, [nextGameState, this, colorPlaying]() -> double {
                return alphaBeta(nextGameState, depth - 1, false, -INF, INF, colorPlaying).value;
            }));
        }

        Move bestMove = Move::passing();
        double bestScore = -INF;
        for (int i = 0; i < moves.size(); i ++) {
            double res = branchResults[i].get();
            if (res > bestScore) {
                bestScore = res;
                bestMove = moves[i];
            }
        }

        return bestMove;
    }
}

AlphaBetaPlayer::~AlphaBetaPlayer() {

}
