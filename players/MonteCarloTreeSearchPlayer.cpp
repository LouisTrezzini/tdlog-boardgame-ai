#include <random>
#include <chrono>
#include <map>

#include "MonteCarloTreeSearchPlayer.h"
#include "../game/Node.h"
#include "../game/Game.h"

std::unique_ptr<Node> MonteCarloTreeSearchPlayer::computeTree(const GameState& rootState) const {
    auto root = std::unique_ptr<Node>(new Node(rootState));

    unsigned long int nbSim = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    while(std::chrono::system_clock::now() - start < std::chrono::duration<double>(0.1) ){
        auto node = root.get();
        GameState curState = rootState;

        // Select a path through the tree to a leaf node.
        while(!node->hasUntriedMoves() && node->hasChildren()){
            node = node->selectChildUCT();

            Game::applyMove(curState, node->getMove());
        }

        // If we are not already at the final state, expand the tree with a new node and move there.
        if (node->hasUntriedMoves()) {
            auto move = node->getUntriedMove();
            Game::applyMove(curState, node->getMove());
            node = node->addChild(move, curState);
        }

        // We now play randomly until the game ends.
        while (Game::hasLegalMoves(curState)) {
            Game::applyMove(curState, Game::getRandomMove(curState));
        }

        // We have now reached a final state. Backpropagate the result
        // up the tree to the root node.
        while (node != nullptr) {
            node->update(Game::getWinner(curState) == getColor());
            node = node->getParent();
        }
    }

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    return root;
}

Move MonteCarloTreeSearchPlayer::getAction(const GameState& gameState) const {
    auto moves = Game::getLegalMoves(gameState);

    if(moves.empty())
        return Move::passing();
    if(moves.size() == 1)
        return moves[0];

    auto root = computeTree(gameState);

    std::map<Move, int> plays;
    std::map<Move, int> wins;

    for (auto child = root->getChildren().cbegin(); child != root->getChildren().cend(); ++child) {
        plays[(*child)->getMove()] += (*child)->getPlays();
        wins[(*child)->getMove()]   += (*child)->getWins();
    }

    // Find the node with the highest score.
    double bestScore = -1;
    Move bestMove = Move::passing();
    for (auto itr: plays) {
        auto move = itr.first;
        double p = itr.second;
        double w = wins[move];
        // Expected success rate assuming a uniform prior (Beta(1, 1)).
        // https://en.wikipedia.org/wiki/Beta_distribution
        double expected_success_rate = (w + 1) / (p + 2);
        if (expected_success_rate > bestScore) {
            bestMove = move;
            bestScore = expected_success_rate;
        }
    }

    return bestMove;
}

MonteCarloTreeSearchPlayer::~MonteCarloTreeSearchPlayer() {

}




