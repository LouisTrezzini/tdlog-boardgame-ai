#include <random>
#include "Statistics.h"
#include "RandomPlayer.h"
#include "../game/Game.h"

//TODO Exception vecteurs vide
double mean(std::vector<double> vec) {
    double result = 0;
    for (int i = 0; i < vec.size(); i ++) {
        result += vec[i];
    }
    return result/vec.size();
}

//TODO Exception vecteurs vide
double standardDeviation(std::vector<double> vec) {
    double thisMean = mean(vec);
    double result = 0;
    for (int i = 0; i < vec.size(); i ++) {
        result += pow(vec[i] - thisMean, 2);
    }
    return sqrt(result/vec.size());
}

void LoiDesGainsSurXParties(int nbGame, IPlayer *player1, int sizeGrid) {
    IPlayer *player2 = new RandomPlayer(false);

    //FIXME Faire passer en variable globale
    int numberOfRounds = 100;

    std::vector<double> gamesWon(numberOfRounds, 0);
    for (int gameRound = 0; gameRound <= numberOfRounds; gameRound ++) {
        for (int i = 0; i < nbGame; i ++) {
            Game game(sizeGrid, player1, player2);
            game.playGameWithoutDisplay();

            if (game.getWinner(game.getGameState()) == Color::WHITE) {
                gamesWon[gameRound] += 1;
            }
        }
    }
    std::cout << mean(gamesWon) << std::endl;
    std::cout << standardDeviation(gamesWon) << std::endl;

    delete player2;
}





