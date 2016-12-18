#ifndef TDLOG_BOARDGAME_GENETICALALGORITHM_H
#define TDLOG_BOARDGAME_GENETICALALGORITHM_H


#include "../Evaluation/LinearCombinationOverTimeEvaluation.h"
#include "../Evaluation/EvaluationFunction.h"
#include "../Evaluation/PawnNumberEvaluation.h"
#include "../Evaluation/PositionEvaluation.h"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Individu {
private:
    vector<double> coefficients;
    vector<EvaluationFunction*> fonctions;
    int score;

public:
    Individu(const vector<double>& coefficients_, const vector<EvaluationFunction*>& fonctions_) {
        score = 0;
        coefficients = coefficients_;
        fonctions = fonctions_;
    }

    int getScore() const {
        return score;
    }
    vector<double> getCoefficients() const{
        return coefficients;
    }

    vector<EvaluationFunction*> getEvaluationFunctions() const {
        return fonctions;
    }

    void incrementeScore() {
        score += 1;
    }

    void setNullScore() {
        score = 0;
    }

    bool operator<(Individu individu) const{
        return (score < individu.score);
    }

    double operator[](int i) {
        return coefficients[i];
    }

    void mutate() {
        for (int i = 0; i < coefficients.size(); i ++) {
            //FIXME
            // Faire passer le 0.1 en variable, et retravailler l'étape de mutation
            if (rand()/(double)RAND_MAX < 0.1) {
                coefficients[i] = rand()/(double)RAND_MAX;
            }
        }
    }

    static Individu makeChild(Individu indiv1, Individu indiv2) {
        // FIXME
        // Exception si les 2 individus ne sont pas de la même espèce
        vector<double> coefs;
        for (int i = 0; i < indiv1.coefficients.size(); i ++) {
            if (rand()%2) {
                coefs.push_back(indiv1[i]);
            }
            else {
                coefs.push_back(indiv2[i]);
            }
        }
        return Individu(coefs, indiv1.fonctions);
    }
};

void InitialisationPopulation(int N, vector<Individu>& population,
                              vector<EvaluationFunction*> evaluationfunctions, int turns){
    for(int i=0; i<N; i++){
        vector<double> coefficients;
        for (int j = 0; j < turns * evaluationfunctions.size(); j ++) {
            coefficients.push_back(rand()/(double)RAND_MAX);
        }
        population.push_back(Individu(coefficients, evaluationfunctions));
    }
}



bool winPlaying(const Individu& individu, int sizeGrid){

    shared_ptr<EvaluationFunction> evalForPlayer1(
            new LinearCombinationOverTimeEvaluation(individu.getCoefficients(), individu.getEvaluationFunctions()));
    IPlayer* player1 = new MinMaxPlayer(evalForPlayer1);

    //FIXME
    // Contre qui faut-il entraîner notre algorithme ???
    IPlayer* player2 = new RandomPlayer();

    Game game(sizeGrid, player1, player2);
    game.playGameWithoutDisplay();

    if (game.getWinner(game.getGameState()) == Color::WHITE){
       return true;
    }
}

void Competition(vector<Individu>& population, int sizeGrid, int gamesToPlay){
    for(int i=0; i<population.size(); ++i){
        for (int j = 0; j < gamesToPlay; j ++) {
            if (winPlaying(population[i], sizeGrid)){
                population[i].incrementeScore();
            }
        }
    }
}



void Selection(vector<Individu>& population,
                int numberToChange) {

    //FIXME
    // Exception si le nombre de sélectionné est trop grand ou trop petit

    for (int i = 0; i < numberToChange; i ++) {
        int k = rand()%(population.size() - numberToChange) + numberToChange;
        int j = rand()%(population.size() - numberToChange) + numberToChange;
        population[i] = Individu::makeChild(population[k], population[j]);
    }
}


void Mutation (vector<Individu>& population, double chancesToMute){
    for (int i = 0; i < population.size(); i ++) {
        if (rand()/(double)RAND_MAX < chancesToMute) {
            population[i].mutate();
        }
    }
}



void GeneticalAlgorithm (int N, int nbiteration,
                         int sizeGrid, int gamesToPlay){

    // Initialisation de l'aléaoire
    srand (time(NULL));

    // Déinition des fonctions d'évaluation que nous allons utiliser
    vector<EvaluationFunction*> evaluationfunctions;
    evaluationfunctions.push_back(new PawnNumberEvaluation());
    evaluationfunctions.push_back(new PositionEvaluation());

    // Définition de notre population
    vector<Individu> population;
    InitialisationPopulation(N, population, evaluationfunctions, pow(sizeGrid, 2) - 4);


    // Boucle de vie de l'algorithme
    int iteration = 0;
    while (iteration < nbiteration){
        Competition(population, sizeGrid, gamesToPlay);
        sort(population.begin(), population.end());
        for (int i = 0; i < population.size(); i ++ ) {
            cerr << population[i].getScore() << " ";
        }
        cerr << endl;

        //FIXME
        //Faire passer le nombre 5 en variable (c'est le nombre d'individu à changer)
        //Faire passer le nombre 0.01 en variable (c'est le purcentage de chance de muter)
        Selection(population, 5);
        Mutation(population, 0.01);
        iteration ++;
        for (int i = 0; i < population.size(); i ++ ) {
            population[i].setNullScore();
        }
    }
}




#endif //TDLOG_BOARDGAME_GENETICALALGORITHM_H
