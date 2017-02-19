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

            IPlayer *enemy = new RandomPlayer(false);

            GeneticalAlgorithm(50, 500, 100, enemy);
            delete enemy;
        }
            break;

        // Moyenne et écart type pour des combinaisons linéaires sur le temps
        case 1: {

            srand(time(NULL));

            vector<std::shared_ptr<IEvaluationFunction>> evaluationFunctions;
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new PawnNumberEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new MobilityEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new TimeEvaluation());

            vector<double> coefficients;
            for (int j = 0; j < 60 * evaluationFunctions.size(); j++) {
                coefficients.push_back(rand() / (double) RAND_MAX);
            }

            shared_ptr<IEvaluationFunction> evalForPlayer1(
                    new LinearCombinationOverTimeEvaluation(coefficients, evaluationFunctions));

            IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 1, false);

            LoiDesGainsSurXParties(100, player1);

            delete player1;
            evalForPlayer1.reset();

            evaluationFunctions[0].reset();
            evaluationFunctions[1].reset();
            evaluationFunctions[2].reset();
            evaluationFunctions[3].reset();
        }
            break;

        // Moyenne et écart type pour des combinaisons linéaires sans temps
        case 2: {
            srand(time(NULL));

            vector<std::shared_ptr<IEvaluationFunction> > evaluationFunctions;
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new PawnNumberEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new MobilityEvaluation()));
            evaluationFunctions.push_back(std::shared_ptr<IEvaluationFunction>(new TimeEvaluation());


            vector<double> coefficients;
            for (int j = 0; j < evaluationFunctions.size(); j++) {
                coefficients.push_back(rand() / (double) RAND_MAX);
            }

            shared_ptr<IEvaluationFunction> evalForPlayer1(
                    new LinearCombinationEvaluation(coefficients, evaluationFunctions));

            IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 1, false);

            LoiDesGainsSurXParties(100, player1);

            delete player1;
            evalForPlayer1.reset();

            evaluationFunctions[0].reset();
            evaluationFunctions[1].reset();
            evaluationFunctions[2].reset();
            evaluationFunctions[3].reset();

        }
            break;

        case 3: {
            IPlayer* player1 = new MonteCarloTreeSearchPlayer(false);
            IPlayer* player2 = new AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()), 5, false);

            Game game(8, player1, player2);

            game.playGame();

            std::cout << game.getWinner(game.getGameState()) << std::endl;
        }
            break;

        //Calcul du temps nécessaire en moyenne pour jouer pour un joueur donné (player2)
        case 4: {
            IPlayer* player1 = new RandomPlayer(false);
            IPlayer* player2 = new AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()), 9, false);


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

        case 5: {
            IPlayer* player1 = new RandomPlayer(false);
            IPlayer* player2 = new AlphaBetaPlayer(std::shared_ptr<IEvaluationFunction>(new PositionEvaluation()), 5, false);

            Game game(8, player1, player2);
            game.playGameWithoutDisplay();
        }
    }

    return 0;
}
