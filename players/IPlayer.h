#ifndef TDLOG_BOARDGAME_AI_IPLAYER_H
#define TDLOG_BOARDGAME_AI_IPLAYER_H

#include <vector>
#include "../game/Color.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include "../evaluation/EndGameEvaluation.h"
#include "../evaluation/PawnNumberEvaluation.h"
#include "../evaluation/IEvaluationFunction.h"

/**
 * Abstract class for all players
 */
class IPlayer {
    Color color;
    float timeRemainingToPlay;
protected:
    bool bestFinish;
public:

    Color getColor() const {
        return color;
    }

    void setColor(Color color) {
        IPlayer::color = color;
    }

    float getTimeRemainingToPlay() const {
        return timeRemainingToPlay;
    }

    void setTimeRemainingToPlay (float time) {
        timeRemainingToPlay = time;
    }

    virtual bool isHuman() {
        return false;
    }


    virtual Move getAction(const GameState& gameState) = 0;
    
    virtual Move getBasicAction(const GameState& gameState) = 0;
    
    virtual Move getActionStoringTime(const GameState& gameState, std::vector<double> &timeNeededToPlay) const;

    virtual ~IPlayer() = 0;
};

inline IPlayer::~IPlayer() { }


#endif //TDLOG_BOARDGAME_AI_IPLAYER_H
