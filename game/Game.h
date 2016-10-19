#ifndef TDLOG_BOARDGAME_AI_GAME_H
#define TDLOG_BOARDGAME_AI_GAME_H

#include "Board.h"
#include "../players/IPlayer.h"
#include "GameState.h"
#include "Move.h"

#include <string>

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

    std::string toString() const;

    const GameState& getGameState() const;

    static std::vector<Move> legalMoves(const GameState& gameState);

    static bool isValidMove(const GameState& gameState, const Move& move);

    static GameState applyMove(const GameState& gameState, const Move& move);

    static Color getWinner(const GameState& gameState);
};

#endif //TDLOG_BOARDGAME_AI_GAME_H
