#ifndef TDLOG_BOARDGAME_EVALUATIONFUNCTION_H
#define TDLOG_BOARDGAME_EVALUATIONFUNCTION_H


#include <iostream>
#include <random>
#include <vector>
#include "../game/Color.h"
#include "../game/Game.h"

using namespace std;

class GeneticalEvaluationFunction {

    vector<vector<int>> valueOfCases;
    vector<double> mobility;
    vector<double> position;
    vector<double> numberOfStones;

public:

    GeneticalEvaluationFunction(){}

    GeneticalEvaluationFunction(const vector<double>& mob,
                                const vector<double>& pos,
                                const vector<double>& nub){

        mobility = mob;
        position = pos;
        numberOfStones = nub;

        valueOfCases[0] = {99, -8, 8, 6, 6, 8, -8, 99};
        valueOfCases[1] = {-8, -24, -4, -3, -3, -4, -24, -8};
        valueOfCases[2] = {8, -4, 7, 4, 4, 7, -4, 8};
        valueOfCases[3] = {6, -3, 4, 0, 0, 4, -3, 6};
        valueOfCases[4] = valueOfCases[3];
        valueOfCases[5] = valueOfCases[2];
        valueOfCases[6] = valueOfCases[1];
        valueOfCases[7] = valueOfCases[0];

    }

    ~GeneticalEvaluationFunction(){
    }

    float getEvaluationMove (GameState gameState, Move move) {

        cout << "okla" << endl;

        GameState nextGameState = gameState;
        Game::applyMove(nextGameState, move);

        int numberOfTurnsPlayed = nextGameState.getBoard().getBlackStones()
                                 + nextGameState.getBoard().getWhiteStones()
                                 - 4;
        Color colorPlaying = nextGameState.getColorPlaying();



        if (colorPlaying == Color::BLACK){
            numberOfTurnsPlayed = numberOfTurnsPlayed/2;
        }
        if (colorPlaying == Color::WHITE){
            numberOfTurnsPlayed = (numberOfTurnsPlayed -1)/2;
        }

        int numberOfmobility = Game::getLegalMoves(nextGameState).size();

        double value = mobility[numberOfTurnsPlayed] * numberOfmobility/10
                       + position[numberOfTurnsPlayed] * valueOfCases[move.getX()][move.getY()]/100
                       + numberOfStones[numberOfTurnsPlayed] * nextGameState.getBoard().getStonesByColor(colorPlaying)/64;

        return float(value);
    }

};

#endif //TDLOG_BOARDGAME_EVALUATIONFUNCTION_H
