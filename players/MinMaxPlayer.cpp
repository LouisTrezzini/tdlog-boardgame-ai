#include "MinMaxPlayer.h"
#include "../game/Game.h"
#include "../game/Move.h"
#include <cmath>
#include <iostream>

const float INF = 1 / 0.f;


MinMaxPlayer::MinMaxPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_, bool bestFinish_, float timeRemainingToPlay_) {
    evaluationFunction = eval;
    depth = depth_;
    bestFinish = bestFinish_;
    setTimeRemainingToPlay (timeRemainingToPlay_);
}

MinMaxOutput MinMaxPlayer::minMax(const GameState& gameState, int depth, bool isMyTurn, Color colorPlaying,
                                  std::chrono::time_point<std::chrono::system_clock>  start) {

    if (getTimeRemainingToPlay() == 0){
        return minMaxDepth(gameState, depth, isMyTurn, colorPlaying, start);
    }
    else{
        return minMaxLength(gameState, isMyTurn, colorPlaying, start);
    }

}

MinMaxOutput MinMaxPlayer::minMaxLength(const GameState& gameState, bool isMyTurn, Color colorPlaying,
                                        std::chrono::time_point<std::chrono::system_clock>  start) {

    int turn = gameState.getBoard().getBlackStones() + gameState.getBoard().getWhiteStones() - InitialStones;
    int totalTurn = pow(gameState.getBoard().getSize(), 2) - InitialStones;
    int remainingTurns = totalTurn - turn;
    if (remainingTurns%2 == 0){
        remainingTurns /= 2;
    }
    else {
        remainingTurns += 1;
        remainingTurns /=2;
    }

    float timeRemainingPerTurn = getTimeRemainingToPlay()/remainingTurns;

    //TO DO améliorer la gestion du calcul de la profondeur
    //Commencer avec une profondeur plus grande ?
    //Stocker les profondeur utilisée dans l'attribut depth ?
    int turnDepth = 1;
    MinMaxOutput result = MinMaxOutput(Game::getRandomMove(gameState),0);

    double timePassedForDepth = 0;

    //Le facteur 10 est - il bon ?
    while (timeRemainingPerTurn > 10 * timePassedForDepth){
        auto startTimeDepth = std::chrono::system_clock::now();

        result = minMaxDepth(gameState, turnDepth, isMyTurn, colorPlaying, start);

        turnDepth += 1;
        double timePassedForDepth = (std::chrono::system_clock::now() - startTimeDepth).count()/std::chrono::milliseconds::period::den;
        setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassedForDepth/1000000);
        timeRemainingPerTurn -= timePassedForDepth;
    }

    return result;
}

MinMaxOutput MinMaxPlayer::minMaxDepth(const GameState& gameState, int depth, bool isMyTurn, Color colorPlaying,
                                       std::chrono::time_point<std::chrono::system_clock>  start) const {
    if (gameState.getBoard().isFull() || depth <= 0) {
        std::chrono::duration<double> timePassed = std::chrono::system_clock::now() - start;
        if (not(isMyTurn)){
            timePassed = -timePassed;
        }
        return MinMaxOutput(Move::passing(), (*evaluationFunction)(gameState, colorPlaying, timePassed.count()));
    }
    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = minMaxDepth(nextGameState, depth - 1, false, colorPlaying, start);
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
                MinMaxOutput moveResult = minMaxDepth(nextGameState, depth - 1, true, colorPlaying, start);
                moveResult.move = moves[i];
                bestResult.min(moveResult);
            }
            return bestResult;
        }
    }
}

Move MinMaxPlayer::getBasicAction(const GameState& gameState) {

    if (false || depth == 1) {
        GameState nextGameState = gameState;
        auto start = std::chrono::system_clock::now();
        MinMaxOutput resultat = minMax (nextGameState, depth, true, gameState.getColorPlaying(), start);
        double timePassed = (std::chrono::system_clock::now() - start).count()/std::chrono::milliseconds::period::den;
        setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
        return resultat.move;
    }
    else {
        Color colorPlaying = gameState.getColorPlaying();
        auto moves = Game::getLegalMoves(gameState);
        std::vector<std::future<double>> branchResults;
        auto startTime = std::chrono::system_clock::now();

        for  (int i = 0; i < moves.size(); i ++) {
            GameState nextGameState = gameState;
            Game::applyMove(nextGameState, moves[i]);
            branchResults.push_back(std::async(std::launch::async, [nextGameState, this, colorPlaying]() -> double {
                auto start = std::chrono::system_clock::now();
                return minMax(nextGameState, depth - 1, true, colorPlaying, start).value;
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

MinMaxPlayer::~MinMaxPlayer() {

}
