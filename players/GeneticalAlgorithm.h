#ifndef TDLOG_BOARDGAME_GENETICALALGORITHM_H
#define TDLOG_BOARDGAME_GENETICALALGORITHM_H


#include "GeneticalPlayer.h"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

void InitialisationPopulation(int N, vector<GeneticalPlayer>& population){

    for(int i=0; i<N; i++){
        population[i] = GeneticalPlayer();
    }
}

int Evaluation (GeneticalPlayer& player1, GeneticalPlayer& player2){

    Game game(8, &player1, &player2);

    game.playGame();

    while (game.getWinner(game.getGameState()) == Color::EMPTY){
    }

    if (game.getWinner(game.getGameState()) == Color::BLACK){
       return 1;
    }
    if (game.getWinner(game.getGameState()) == Color::WHITE){
        return 2;
    }
}

void Classement (vector<GeneticalPlayer>& players, vector<int>& ranking){
    int size = players.size();

    for(int i=0; i<size; ++i){
        for (int j=i+1; j<size; ++j){
            int winner = Evaluation(players[i], players[j]);
            if (winner = 1){
                ranking[i]++;
            }
            else{
                ranking[j]++;
            }
        }
    }
}

void Selection (const vector<GeneticalPlayer>& players,
                const vector<int>& ranking,
                vector<GeneticalPlayer>& selectionnated,
                int numberSelectionnated){

    int size = players.size();
    numberSelectionnated = min(size, numberSelectionnated);

    int sum = 0;
    for (int i=0; i<size; i++){
        sum += ranking[i];
    }

    while (numberSelectionnated >0){
        int random = rand()%sum;
        int aleat = 0;
        int i = 0;
        while (aleat < random){
            aleat+=ranking[i];
            i++;
        }
        selectionnated.push_back(players[i-1]);
        numberSelectionnated--;
    }

    while (selectionnated.size() < size){
        selectionnated.push_back(GeneticalPlayer());
    }
}

void Mutation (vector<GeneticalPlayer>& players,
               vector<GeneticalPlayer>& mutedPlayers){

    int size = players.size();

    while (players.size()>3){
        int lowbound = rand()%30;
        int upperbound = rand()%60 + 31;
        for(int i=lowbound; i<upperbound; i++){
            std::swap(players[0].mobility[i], players[1].mobility[i]);
            std::swap(players[1].mobility[i], players[2].mobility[i]);
            std::swap(players[0].position[i], players[2].position[i]);
            std::swap(players[1].position[i], players[2].position[i]);
            std::swap(players[0].numberOfStones[i], players[1].numberOfStones[i]);
            std::swap(players[1].numberOfStones[i], players[2].numberOfStones[i]);
        }

        mutedPlayers.push_back(players[0]);
        mutedPlayers.push_back(players[1]);
        mutedPlayers.push_back(players[2]);

        players.erase(players.begin(), players.begin()+2);
    }

    while (mutedPlayers.size() < size){
        mutedPlayers.push_back(GeneticalPlayer());
    }
}

void toString (GeneticalPlayer& player){

    int size = player.mobility.size();

    cout << "Mobility   Position   NumberOfStones" <<endl;
    cout << "------------------------------------" << endl;
    cout << endl;

    for (int i=0; i<size; i++){
        cout << player.mobility[i] << "          ";
        cout << player.position[i] << "          ";
        cout << player.numberOfStones[i] << endl;
    }
}


void GeneticalAlgorithm (int N, int nbiteration){

    vector<GeneticalPlayer> population;
    cout << "bala";
    InitialisationPopulation(N, population);

    int iteration = 0;
    cout << "ok avant while" << endl;
    while (iteration < nbiteration){
        vector<int> ranking (N);
        Classement (population, ranking);
        cout << "ok classement " << endl;
        vector<GeneticalPlayer> selection (N);
        Selection (population, ranking, selection, int(0.5*N));
        Mutation(selection, population);
        iteration ++;
    }

    vector<int> ranking (N);
    Classement(population, ranking);

    int maxi = *(max_element(ranking.begin(),ranking.end()));
    int i = 0;
    while (maxi > ranking[i]){
        i++;
    }

    toString(population[i]);
}




#endif //TDLOG_BOARDGAME_GENETICALALGORITHM_H
