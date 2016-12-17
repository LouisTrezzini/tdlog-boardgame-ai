#include "MinMaxPlayer.h"
#include "../game/Game.h"

MinMaxOutput::MinMaxOutput(Move move, float value) {
    MinMaxOutput::move = move;
    MinMaxOutput::value = value;
}

void MinMaxOutput::max(const MinMaxOutput &other) {
    if (value < other.value) {
        value = other.value;
        move = other.move;
    }
}

void MinMaxOutput::min(const MinMaxOutput &other) {
    if (value > other.value) {
        value = other.value;
        move = other.move;
    }
}

MinMaxPlayer::MinMaxPlayer(std::shared_ptr<EvaluationFunction> eval) {
    evaluationFunction = eval;
}

MinMaxOutput MinMaxPlayer::minMax(GameState& gameState, int profondeur, bool isMyTurn, Color colorPlaying) const {
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

Move MinMaxPlayer::getAction(const GameState& gameState) const {
    GameState nextGameState = gameState;
    MinMaxOutput resultat = minMax(nextGameState, profondeur, true, gameState.getColorPlaying());
    return resultat.move;
}

MinMaxPlayer::~MinMaxPlayer() {

}




