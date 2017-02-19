#ifndef TDLOG_BOARDGAME_GENETICALALGORITHM_H
#define TDLOG_BOARDGAME_GENETICALALGORITHM_H

#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <thread>
#include <future>

#include "../evaluation/LinearCombinationOverTimeEvaluation.h"
#include "../evaluation/LinearCombinationEvaluation.h"
#include "../evaluation/IEvaluationFunction.h"
#include "../evaluation/PawnNumberEvaluation.h"
#include "../evaluation/PositionEvaluation.h"
#include "../evaluation/MobilityEvaluation.h"
#include "AlphaBetaPlayer.h"

using namespace std;

class Individu {
private:
    vector<double> coefficients;
    vector<std::shared_ptr<IEvaluationFunction>> functions;
    int score;

public:
    Individu(const vector<double>& coefficients, const vector<std::shared_ptr<IEvaluationFunction>>& functions) {
        score = 0;
        this->coefficients = coefficients;
        this->functions = functions;
    }

    int getScore() const {
        return score;
    }

    const vector<double>& getCoefficients() const {
        return coefficients;
    }

    const vector<std::shared_ptr<IEvaluationFunction>>& getEvaluationFunctions() const {
        return functions;
    }

    void incrementeScore() {
        score += 1;
    }

    void setNullScore() {
        score = 0;
    }

    bool operator<(const Individu& individu) const {
        return score < individu.score;
    }

    void mutate(double chancesToMuteForGene) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (rand() / (double) RAND_MAX < chancesToMuteForGene) {
                coefficients[i] = rand() / (double) RAND_MAX;
            }
        }
    }

    static Individu makeChild(const Individu& indiv1, const Individu& indiv2) {
        // FIXME
        // Exception si les 2 individus ne sont pas de la même espèce
        vector<double> coefs;
        for (int i = 0; i < indiv1.coefficients.size(); i++) {
            if (rand() % 2) {
                coefs.push_back(indiv1.getCoefficients()[i]);
            } else {
                coefs.push_back(indiv2.getCoefficients()[i]);
            }
        }
        return Individu(coefs, indiv1.functions);
    }
};

void InitialisationPopulation(int N, vector <Individu>& population,
                              vector<std::shared_ptr<IEvaluationFunction>> evaluationFunctions, int turns) {
    for (int i = 0; i < N; i++) {
        vector<double> coefficients;
        // FIXME Avec le temps, il faudra rajouter un *turns....
        for (int j = 0; j < evaluationFunctions.size(); j++) {
            coefficients.push_back(rand() / (double) RAND_MAX);
        }
        population.push_back(Individu(coefficients, evaluationFunctions));
    }
}


bool winPlaying(const Individu& individu, int sizeGrid, IPlayer *player2) {

    shared_ptr <IEvaluationFunction> evalForPlayer1(
            new LinearCombinationEvaluation(individu.getCoefficients(), individu.getEvaluationFunctions()));
    // FIXME Faire passer en paramètre ?
    IPlayer *player1 = new AlphaBetaPlayer(evalForPlayer1, 3, false);

    Game game(sizeGrid, player1, player2);
    game.playGameWithoutDisplay();

    evalForPlayer1.reset();
    delete player1;

    return game.getWinner(game.getGameState()) == Color::WHITE;
}

void Competition(vector <Individu>& population, int sizeGrid, int gamesToPlay, IPlayer *enemy) {
    for (int i = 0; i < population.size(); ++i) {
        vector<future<bool>> resultsFuture;

        for (int j = 0; j < gamesToPlay; j++) {
            Individu& individu = population[i];

            resultsFuture.push_back(std::async(std::launch::async, [individu, sizeGrid, enemy]() -> bool {
                return winPlaying(individu, sizeGrid, enemy);
            }));
        }

        for (int j = 0; j < gamesToPlay; j++) {
            if (resultsFuture[j].get()) {
                population[i].incrementeScore();
            }
        }
    }
}


void Selection(vector <Individu>& population, int numberToChange) {
    //FIXME
    // Exception si le nombre de sélectionné est trop grand ou trop petit

    for (int i = 0; i < numberToChange; i++) {
        int k = rand() % (population.size() - numberToChange) + numberToChange;
        int j = rand() % (population.size() - numberToChange) + numberToChange;
        population[i] = Individu::makeChild(population[k], population[j]);
    }
}


void Mutation(vector <Individu>& population, double chancesToMute, double chancesToMuteForGene) {
    for (int i = 0; i < population.size(); i++) {
        if (rand() / (double) RAND_MAX < chancesToMute) {
            population[i].mutate(chancesToMuteForGene);
        }
    }
}


void GeneticalAlgorithm(int N, int nbiteration,
                         int gamesToPlay, IPlayer *enemy, double chancesToMute = 0.01, double chancesToMuteForGene = 0.1,
                        int nbDeath = 5, int sizeGrid = 8) {

    // Initialisation de l'aléatoire
    srand(time(NULL));

    // Déinition des functions d'évaluation que nous allons utiliser
    vector < std::shared_ptr<IEvaluationFunction> > evaluationFunctions;

    evaluationFunctions.push_back(shared_ptr<IEvaluationFunction>(new PawnNumberEvaluation()));
    evaluationFunctions.push_back(shared_ptr<IEvaluationFunction>(new PositionEvaluation()));
    evaluationFunctions.push_back(shared_ptr<IEvaluationFunction>(new MobilityEvaluation()));

    // Définition de notre population
    vector <Individu> population;
    InitialisationPopulation(N, population, evaluationFunctions, pow(sizeGrid, 2) - 4);


    // Boucle de vie de l'algorithme
    int iteration = 0;
    while (iteration < nbiteration) {
        Competition(population, sizeGrid, gamesToPlay, enemy);
        sort(population.begin(), population.end());
        for (int i = 0; i < population.size(); i++) {
            cerr << population[i].getScore() << " ";
        }
        cerr << endl;

        for(auto coeff: population[0].getCoefficients()){
            cerr << coeff << " ";
        }
        cerr << endl;

        Selection(population, nbDeath);
        Mutation(population, chancesToMute, chancesToMuteForGene);
        iteration++;
        for (int i = 0; i < population.size(); i++) {
            population[i].setNullScore();
        }
    }
    for (int i = evaluationFunctions.size() - 1; i >= 0; i --) {
        evaluationFunctions[i].reset();
    }
}


#endif //TDLOG_BOARDGAME_GENETICALALGORITHM_H
