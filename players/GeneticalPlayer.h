#ifndef TDLOG_BOARDGAME_AI_GENETICALPLAYER_H
#define TDLOG_BOARDGAME_AI_GENETICALPLAYER_H


#include <vector>
#include <random>
#include "GeneticalEvaluationFunction.h"
#include "../game/Move.h"
#include "../game/Game.h"
#include "MinMaxPlayer.h"

class GeneticalPlayer: public IPlayer {
public:

    vector<double> mobility;
    vector<double> position;
    vector<double> numberOfStones;
    GeneticalEvaluationFunction eval;



    GeneticalPlayer(){

        for(int i=0; i<60; ++i){
            int valuemobility = rand()%100;
            int valueposition = rand()%100;
            int valuenumberOfStones = rand()%100;
            int sum = valuemobility + valueposition + valuenumberOfStones;
            mobility[i] = valuemobility/sum*100;
            position[i] = valueposition/sum*100;
            numberOfStones[i] = valuenumberOfStones/sum*100;
        }

        eval = GeneticalEvaluationFunction(mobility, position, numberOfStones);
    }

    ~GeneticalPlayer();

    vector<double> getMobility() const {
        return mobility;
    }

    vector<double> getPosition() const {
        return position;
    }

    vector<double> getNumberOfStones() const {
        return numberOfStones;
    }


    GeneticalEvaluationFunction getEval () const {
        return eval;
    }

    MinMaxOutput minMax(GameState& gameState, Move move, int profondeur, bool isMyTurn) const;

    Move getAction(const GameState& gameState) const;

};

#endif //TDLOG_BOARDGAME_AI_GENETICALPLAYER_H
