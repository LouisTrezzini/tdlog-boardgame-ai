#ifndef TDLOG_BOARDGAME_AI_IPLAYER_H
#define TDLOG_BOARDGAME_AI_IPLAYER_H

#include <vector>
#include "../game/Color.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include <string>

/**
 * Abstract class for all players
 */
class IPlayer {
    Color color;

public:
    Color getColor() const {
        return color;
    }

    void setColor(Color color) {
        IPlayer::color = color;
    }

    virtual Move getAction(const GameState& gameState) const = 0;
    virtual ~IPlayer() = 0;
};

inline IPlayer::~IPlayer() { };


#endif //TDLOG_BOARDGAME_AI_IPLAYER_H
