#include <random>
#include <chrono>
#include <map>
#include <iostream>

#include "MonteCarloTreeSearchPlayer.h"
#include "../game/Node.h"
#include "../game/Game.h"

using namespace std;

std::unique_ptr<Node> MonteCarloTreeSearchPlayer::computeTree(const GameState& rootState) const {
    auto root = std::unique_ptr<Node>(new Node(rootState));

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    end = start + std::chrono::seconds(6);

    srand(time(NULL));

    while(std::chrono::system_clock::now() < end){
        auto node = root.get();

        // 1. Selection
        // Select a path through the tree to a leaf node.
        while(!node->hasUntriedMoves() && node->hasChildren()){
            node = node->selectChildUCT(getColor());
        }

        // 2. Expansion
        // If we are not already at the final state, expand the tree with a new node and move there.
        if (node->hasUntriedMoves()) {
            auto move = node->getUntriedMove();
            GameState newState = node->getGameState();
            Game::applyMove(newState, move);
            node = node->addChild(move, newState);
        }

        // 3. Simulation
        // We now play randomly until the game ends.
        GameState curState = node->getGameState();
        Color colorPlaying = curState.getColorPlaying();

        while (Game::getWinner(curState) == Color::EMPTY) {
            Game::applyMove(curState, Game::getRandomMove(curState));
        }

        // 4. Backpropagation
        // We have now reached a final state. Backpropagate the result up the tree to the root node.
        bool hasWon = Game::getWinner(curState) == getColor();
        while (node != nullptr) {
            node->update(hasWon);
            node = node->getParent();
        }
    }

    end = std::chrono::system_clock::now();

    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cerr << "MonteCarlo played " << root.get()->getPlays() << " games in " << elapsedSeconds << "s" << std::endl;

    for (auto child: root.get()->getChildren()) {
        std::cerr << child->getMove().toString() << ": (" << child->getWins() << "/" << child->getPlays() << ") "
                  << double(child->getWins()) / child->getPlays()
                  << std::endl;
    }

    return root;
}

Move MonteCarloTreeSearchPlayer::getAction(const GameState& gameState) {
    auto moves = Game::getLegalMoves(gameState);
    auto startTime = std::chrono::system_clock::now();

    if(moves.empty())
        return Move::passing();

    if(moves.size() == 1)
        return moves[0];

    // TODO parallelization

    auto root = computeTree(gameState);

//    // Find the node with the best score
//    double bestScore = -1;
//    Move bestMove = Move::passing();
//    for(auto child: root->getChildren()){
//        int w = child->getWins();
//        int p = child->getPlays();
//        // Expected success rate assuming a uniform prior (Beta(1, 1)).
//        // https://en.wikipedia.org/wiki/Beta_distribution
//        double expected_success_rate = (w + 1) / (p + 2);
//        if (expected_success_rate > bestScore) {
//            bestMove = child->getMove();
//            bestScore = expected_success_rate;
//        }
//    }

    // Find the node with the most plays
    int mostPlays = -1;
    int mostWins = -1;
    std::vector<Move> bestMoves;
    for(auto child: root->getChildren()){
        int wins = child->getWins();
        int plays = child->getPlays();

        if (plays > mostPlays){
            mostPlays = plays;
            mostWins = wins;
            bestMoves.clear();
            bestMoves.push_back(child->getMove());
        }

        else if (plays == mostPlays){
            if (wins > mostWins) {
                mostWins = wins;
                bestMoves.clear();
                bestMoves.push_back(child->getMove());
            }
            else if (wins == mostWins) {
                bestMoves.push_back(child->getMove());
            }
        }
    }
    double timePassed = (std::chrono::system_clock::now() - startTime).count()/std::chrono::milliseconds::period::den;
    setTimeRemainingToPlay(getTimeRemainingToPlay() - timePassed/1000000);
    return bestMoves[rand() % bestMoves.size()];
}

MonteCarloTreeSearchPlayer::~MonteCarloTreeSearchPlayer() {

}




