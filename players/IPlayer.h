#ifndef TDLOG_BOARDGAME_AI_IPLAYER_H
#define TDLOG_BOARDGAME_AI_IPLAYER_H

#include <vector>
#include "../game/Color.h"
#include "../game/Move.h"
#include "../game/GameState.h"

/**
 * Abstract class for all players
 */
class IPlayer {
    Color color;

    IPlayer() {};

public:
    Color getColor(){
        return color;
    }

    void setColor(Color color) {
        IPlayer::color = color;
    }

    virtual Move getAction(const GameState& gameState, const std::vector<Move>& legalMoves) const = 0;
    virtual ~IPlayer() = 0;
};

inline IPlayer::~IPlayer() { };


#endif //TDLOG_BOARDGAME_AI_IPLAYER_H
