//
// Created by till034 on 10/15/16.
//

#ifndef TDLOG_BOARDGAME_AI_GAME_H
#define TDLOG_BOARDGAME_AI_GAME_H

#include "Board.h"
#include "../players/IPlayer.h"
#include "GameState.h"
#include "Move.h"

/**
 * A class that enforces the game rules
 */
class Game {
    GameState gameState;
    IPlayer* whitePlayer;
    IPlayer* blackPlayer;

public:
    Game(int size, IPlayer* whitePlayer, IPlayer* blackPlayer);

    void playGame();

    Move pickMove(const GameState& gameState) const;

    void playMove(const Move& move);

    void display() const;

    const GameState& getGameState() const;

    static Move getRandomMove(const GameState& gameState);

    static bool hasLegalMoves(const GameState& gameState);

    static std::vector<Move> getLegalMoves(const GameState& gameState);

    static bool isValidMove(const GameState& gameState, const Move& move);

    static void applyMove(GameState& gameState, const Move& move);

    static Color getWinner(const GameState& gameState);
};


#endif //TDLOG_BOARDGAME_AI_GAME_H
