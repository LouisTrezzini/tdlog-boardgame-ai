#include "MinMaxPlayer.h"
#include "../game/Game.h"

const float INF = 1 / 0.f;
const int profondeur = 7;


MinMaxOutput MinMaxPlayer::minMax(GameState& gameState, int profondeur, bool isMyTurn) const {
    if (gameState.getBoard().isFull() || profondeur <= 0) {
        // Fonction d'évaluation trèèèèès mauvaise
        return MinMaxOutput(Move::passing(), gameState.getBoard().getStonesByColor(getColor()));
    }
    else {
        if (isMyTurn) {
            MinMaxOutput bestResult(Move::passing(), - INF);
            auto moves = Game::getLegalMoves(gameState);
            for  (int i = 0; i < moves.size(); i ++) {
                GameState nextGameState = gameState;
                Game::applyMove(nextGameState, moves[i]);
                MinMaxOutput moveResult = minMax(nextGameState, profondeur - 1, false);
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
                MinMaxOutput moveResult = minMax(nextGameState, profondeur - 1, true);
                moveResult.move = moves[i];
                bestResult.min(moveResult);
            }
            return bestResult;
        }
    }
}

Move MinMaxPlayer::getAction(const GameState& gameState) const {
    GameState nextGameState = gameState;
    MinMaxOutput resultat = minMax(nextGameState, profondeur, true);
    return resultat.move;
}

MinMaxPlayer::~MinMaxPlayer() {

}




