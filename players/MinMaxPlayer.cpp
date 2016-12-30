#include "MinMaxPlayer.h"
#include "../game/Game.h"

const float INF = 1 / 0.f;


MinMaxPlayer::MinMaxPlayer(std::shared_ptr<IEvaluationFunction> eval, int depth_) {
    evaluationFunction = eval;
    depth = depth_;
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
    MinMaxOutput resultat = minMax(nextGameState, depth, true, gameState.getColorPlaying());
    return resultat.move;
}

MinMaxPlayer::~MinMaxPlayer() {

}




