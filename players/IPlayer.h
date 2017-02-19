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
protected:
    bool bestFinish;
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

    virtual Move getBasicAction(const GameState& gameState) const = 0;
    
    virtual Move getActionStoringTime(const GameState& gameState, std::vector<double> &timeNeededToPlay) const;

    virtual Move getAction(const GameState& gameState) const;

    virtual ~IPlayer() = 0;
};

inline IPlayer::~IPlayer() { };


#endif //TDLOG_BOARDGAME_AI_IPLAYER_H