#ifndef TDLOG_BOARDGAME_AI_IPLAYER_H
#define TDLOG_BOARDGAME_AI_IPLAYER_H

#include <vector>
#include "../game/Color.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include <time.h>

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

    virtual bool isHuman() {
        return false;
    }
    virtual Move getAction(const GameState& gameState) const = 0;
    virtual Move getActionStoringTime(const GameState& gameState, std::vector<double> &timeNeededToPlay) const {
        double startTime = clock();
        Move moveToPlay = getAction(gameState);
        // TODO Exception si timeNeededToPlay n'est pas initialisé correctement
        // TODO Le -4 est moche
        timeNeededToPlay[gameState.getBoard().getTotalStones() - 4] += (-startTime + clock())/(double)CLOCKS_PER_SEC;
        return moveToPlay;
    }
    virtual ~IPlayer() = 0;
};

inline IPlayer::~IPlayer() { };


#endif //TDLOG_BOARDGAME_AI_IPLAYER_H
