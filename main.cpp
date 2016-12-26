#include <iostream>
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "players/GeneticalAlgorithm.h"
#include "game/Game.h"
#include "evaluation/MobilityEvaluation.h"
#include "players/Statistics.h"
#include "evaluation/LinearCombinationEvaluation.h"

int main(int argc, char *argv[]) {

    int mode = 0;
    if(argc >= 2) mode = atoi(argv[1]);
    switch(mode) {

        // Algorithme génétique
        case 0: {
            IPlayer *enemy = new RandomPlayer();
            GeneticalAlgorithm(30, 500, 100, enemy);
            delete enemy;
        }

        // Moyenne et écart type pour des combinaisons linéaires sur le temps
        case 1: {

            srand(time(NULL));

            vector<IEvaluationFunction *> evaluationFunctions;
            evaluationFunctions.push_back(new PawnNumberEvaluation());
            evaluationFunctions.push_back(new PositionEvaluation());
            evaluationFunctions.push_back(new MobilityEvaluation());

            vector<double> coefficients;
            for (int j = 0; j < 60 * evaluationFunctions.size(); j++) {
                coefficients.push_back(rand() / (double) RAND_MAX);
            }

            shared_ptr<IEvaluationFunction> evalForPlayer1(
                    new LinearCombinationOverTimeEvaluation(coefficients, evaluationFunctions));

            IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 1);

            LoiDesGainsSurXParties(100, player1);

            delete player1;
            evalForPlayer1.reset();
            delete evaluationFunctions[0];
            delete evaluationFunctions[1];
            delete evaluationFunctions[2];
        }

        // Moyenne et écart type pour des combinaisons linéaires sans temps
        case 2: {
            srand(time(NULL));

            vector<IEvaluationFunction *> evaluationFunctions;
            evaluationFunctions.push_back(new PawnNumberEvaluation());
            evaluationFunctions.push_back(new PositionEvaluation());
            evaluationFunctions.push_back(new MobilityEvaluation());

            vector<double> coefficients;
            for (int j = 0; j < evaluationFunctions.size(); j++) {
                coefficients.push_back(rand() / (double) RAND_MAX);
            }

            shared_ptr<IEvaluationFunction> evalForPlayer1(
                    new LinearCombinationEvaluation(coefficients, evaluationFunctions));

            IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 1);

            LoiDesGainsSurXParties(100, player1);

            delete player1;
            evalForPlayer1.reset();
            delete evaluationFunctions[0];
            delete evaluationFunctions[1];
            delete evaluationFunctions[2];
        }
    }

    return 0;
}
