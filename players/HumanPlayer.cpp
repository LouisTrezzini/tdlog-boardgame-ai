#include "HumanPlayer.h"
#include "../game/Game.h"
#include <stdexcept>
#include <chrono>
#include <iostream>
using namespace std;

Move HumanPlayer::getAction(const GameState& gameState) {
    auto moves = Game::getLegalMoves(gameState);
    auto startTime = std::chrono::system_clock::now();

    bool moveUnavailable = true;
    Move askedMove = Move::passing();

    while (moveUnavailable) {
        // On demande une entrée à l'utilisateur
        std::cout << "Entrez une abscisse et une ordonnée" << std::endl;
        std::string x, y;
        std::cin >> x;
        std::cin >> y;

        // On entre le Move(y, x) et non Move(x, y) pour correspondre à la notation tableau, plus simple pour l'utilisateur
        try {
            askedMove = Move(std::stoi(y), std::stoi(x));
        }
        catch (const std::invalid_argument& exception) {
            std::cout << "Mouvement invalide !" << std::endl;
            continue;
        }

        // On vérifie si l'entrée est valide
        for (int i = 0; i < moves.size(); ++ i) {
            if (askedMove == moves[i]) {
                moveUnavailable = false;
            }
        }
    }
    double timePassed = (std::chrono::system_clock::now() - startTime).count()/std::chrono::milliseconds::period::den;
    setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
    return askedMove;
}

HumanPlayer::~HumanPlayer() {

}




