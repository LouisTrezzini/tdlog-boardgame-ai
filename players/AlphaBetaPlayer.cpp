#include "../game/Game.h"
#include "AlphaBetaPlayer.h"

const double INF = 1 / 0.f;


AlphaBetaPlayer::AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_, float timeRemainingToPlay_) {
    evaluationFunction = eval;
    depth = depth_;
    bestFinish = bestFinish_;
    setTimeRemainingToPlay(timeRemainingToPlay_);
}

MinMaxOutput AlphaBetaPlayer::alphaBeta(const GameState& gameState,
                                        const std::shared_ptr<IEvaluationFunction> &evalFunction,
                                        int profondeur, bool isMyTurn, double alpha, double beta,
                                        const Color &colorPlaying,
                                        std::chrono::time_point<std::chrono::system_clock>  start) const {

    if (gameState.getBoard().isFull() || profondeur <= 0) {
        std::chrono::duration<double> timePassed = std::chrono::system_clock::now() - start;
        return MinMaxOutput(Move::passing(), (*evalFunction)(gameState, colorPlaying, timePassed.count()));
    }

    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);

                MinMaxOutput moveResult = alphaBeta(nextGameState, evalFunction, profondeur - 1,
                                                    false, alpha, beta, colorPlaying, start);
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
                                                    profondeur - 1, true, alpha, beta, colorPlaying, start);
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


Move AlphaBetaPlayer::getBasicAction(const GameState& gameState) {
    // Sans parallélisation
    if (false || depth == 1) {
        GameState nextGameState = gameState;

        auto start = std::chrono::system_clock::now();
        MinMaxOutput resultat = alphaBeta(nextGameState, evaluationFunction, depth, true, -INF, INF, gameState.getColorPlaying(), start);
        double timePassed = (std::chrono::system_clock::now() - start).count()/std::chrono::milliseconds::period::den;
        setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);

        return resultat.move;
    // Avec parallélisation
    } else {
        Color colorPlaying = gameState.getColorPlaying();
        auto moves = Game::getLegalMoves(gameState);
        std::vector<std::future<double>> branchResults;
        auto startTime = std::chrono::system_clock::now();

        for  (int i = 0; i < moves.size(); i ++) {
            GameState nextGameState = gameState;
            Game::applyMove(nextGameState, moves[i]);

            branchResults.push_back(std::async(std::launch::async, [nextGameState, this, colorPlaying]() -> double {
                auto start = std::chrono::system_clock::now();
                return alphaBeta(nextGameState, evaluationFunction, depth - 1, false, -INF, INF, colorPlaying, start).value;
                return alphaBeta(nextGameState, evaluationFunction, depth - 1, false, -INF, INF, colorPlaying).value;
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
        double timePassed = (std::chrono::system_clock::now() - startTime).count()/std::chrono::milliseconds::period::den;
        setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
        return bestMove;
    }
}

AlphaBetaPlayer::~AlphaBetaPlayer() {

}
