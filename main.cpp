#include <iostream>
#include <cstdlib>

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
            GeneticalAlgorithm(50, 500, 100, enemy);
            delete enemy;
        }
            break;

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
            break;

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
            break;

        case 3: {
            IPlayer* player1 = new MonteCarloTreeSearchPlayer();
            IPlayer* player2 = new AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()), 5);

            Game game(8, player1, player2);

            game.playGame();

            std::cout << game.getWinner(game.getGameState()) << std::endl;
        }
            break;

        //Calcul du temps nécessaire en moyenne pour jouer pour un joueur donné (player2)
        case 4: {
            IPlayer* player1 = new MinMaxPlayer(std::shared_ptr<IEvaluationFunction>(new PawnNumberEvaluation()), 1);
            IPlayer* player2 = new AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction>(new PawnNumberEvaluation()), 6);

            vector<double> timeNeededToPlay(60,0);

            Game game(8, player1, player2);
            game.playGameWithoutDisplayStoringTime(timeNeededToPlay);

            for (int i = 0; i < timeNeededToPlay.size() / 2; i ++) {
                cout << timeNeededToPlay[2 * i] << endl;
            }
            cout << "======" << endl;
            for (int i = 0; i < timeNeededToPlay.size() / 2; i ++) {
                cout << timeNeededToPlay[2 * i + 1] << endl;
            }
        }
            break;
    }

    return 0;
}
