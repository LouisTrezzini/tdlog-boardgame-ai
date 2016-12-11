#include "GeneticalPlayer.h"
#include <iostream>

GeneticalPlayer::~GeneticalPlayer(){
}

MinMaxOutput GeneticalPlayer::minMax(GameState& gameState, Move move, int profondeur, bool isMyTurn) const {
    cout << profondeur << endl;
    if (gameState.getBoard().isFull() || profondeur <= 0) {
        return MinMaxOutput(Move::passing(), getEval().getEvaluationMove(gameState, move));
    }
    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                MinMaxOutput moveResult = minMax(gameState, moves[i], profondeur - 1, false);
                moveResult.move = moves[i];
                bestResult.max(moveResult);
            }
            return bestResult;
        }
        else {
            MinMaxOutput bestResult(Move::passing(), INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                MinMaxOutput moveResult = minMax(gameState, moves[i], profondeur - 1, true);
                moveResult.move = moves[i];
                bestResult.min(moveResult);
            }
            return bestResult;
        }
    }
}

Move GeneticalPlayer::getAction(const GameState& gameState) const {
    GameState nextGameState = gameState;
    MinMaxOutput resultat = minMax(nextGameState, Move::passing(), profondeur, true);
    return resultat.move;
}
