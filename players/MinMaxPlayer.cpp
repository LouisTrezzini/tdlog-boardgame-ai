#include "MinMaxPlayer.h"
#include "../game/Game.h"

const float INF = 1 / 0.f;


MinMaxPlayer::MinMaxPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_) {
    evaluationFunction = eval;
    depth = depth_;
    bestFinish = bestFinish_;
}

MinMaxOutput MinMaxPlayer::minMax(const GameState& gameState, int profondeur, bool isMyTurn, Color colorPlaying) const {
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
                MinMaxOutput moveResult = minMax(nextGameState, profondeur - 1, false, colorPlaying);
                moveResult.move = moves[i];
                bestResult.max(moveResult);
            }
            return bestResult;
        }
        else {
            MinMaxOutput bestResult(Move::passing(), INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = minMax(nextGameState, profondeur - 1, true, colorPlaying);
                moveResult.move = moves[i];
                bestResult.min(moveResult);
            }
            return bestResult;
        }
    }
}

Move MinMaxPlayer::getBasicAction(const GameState& gameState) const {
    if (false || depth == 1) {
        GameState nextGameState = gameState;
        MinMaxOutput resultat = minMax(nextGameState, depth, true, gameState.getColorPlaying());
        return resultat.move;
    }
    else {
        Color colorPlaying = gameState.getColorPlaying();
        auto moves = Game::getLegalMoves(gameState);
        std::vector<std::future<double>> branchResults;

        for  (int i = 0; i < moves.size(); i ++) {
            GameState nextGameState = gameState;
            Game::applyMove(nextGameState, moves[i]);

            branchResults.push_back(std::async(std::launch::async, [nextGameState, this, colorPlaying]() -> double {
                return minMax(nextGameState, depth - 1, false, colorPlaying).value;
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

MinMaxPlayer::~MinMaxPlayer() {

}
