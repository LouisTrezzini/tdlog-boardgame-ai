#include <iostream>
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "players/GeneticalAlgorithm.h"
#include "game/Game.h"
#include "players/Statistics.h"

int main(int argc, char *argv[]) {

    int whatToDo = 1;

    if (whatToDo == 0) {
        GeneticalAlgorithm (30, 500, 30);
    }

    if (whatToDo == 1) {

        srand(time(NULL));

        vector < IEvaluationFunction * > evaluationFunctions;
        evaluationFunctions.push_back(new PawnNumberEvaluation());
        evaluationFunctions.push_back(new PositionEvaluation());

        vector<double> coefficients;
        for (int j = 0; j < 60 * evaluationFunctions.size(); j++) {
            coefficients.push_back(rand() / (double) RAND_MAX);
        }

        shared_ptr <IEvaluationFunction> evalForPlayer1(
                new LinearCombinationOverTimeEvaluation(coefficients, evaluationFunctions));

        IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 1);

        LoiDesGainsSurXParties(30, player1);
    }

    return 0;
}
