#include "HumanPlayer.h"
#include "../game/Game.h"


Move HumanPlayer::getAction(const GameState& gameState) const {
    auto moves = Game::getLegalMoves(gameState);

    bool moveUnavailable = true;
    // Nid à problème si passing devient un legalMove...
    Move askedMove = Move::passing();

    while (moveUnavailable) {
        // On demande une entrée à l'utilisateur
        std::cout << "Entrez une abscisse et une ordonnée" << std::endl;
        std::string x, y;
        std::cin >> x;
        std::cin >> y;

        try {
            askedMove = Move(std::stoi(y), std::stoi(x));
        }
        catch (std::invalid_argument exception) {
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

    return askedMove;
}

HumanPlayer::~HumanPlayer() {

}




