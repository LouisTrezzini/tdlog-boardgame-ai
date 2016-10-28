//
// Created by till034 on 10/28/16.
//

#ifndef TDLOG_BOARDGAME_AI_NODE_H
#define TDLOG_BOARDGAME_AI_NODE_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include "GameState.h"
#include "Move.h"
#include "Game.h"

class Node {
    GameState gameState;
    unsigned int plays;
    unsigned int wins;
    std::vector<Node*> children;
    Node* const parent;

    const Move move;
    std::vector<Move> moves;

    double UCTScore;

public:
    Node(const GameState& gameState, const Move& move = Move::passing(), Node* parent = nullptr)
            : gameState(gameState),
              moves(Game::getLegalMoves(gameState)),
              move(move),
              parent(parent)
    {

    };

    Node* addChild(const Move& move, const GameState& gameState) {
        Node* child = new Node(gameState, move, this);
        children.push_back(child);

        auto itr = moves.begin();
        for (; itr != moves.end() && *itr != move; ++itr);
        moves.erase(itr);

        return child;
    };

    Node* selectChildUCT() const {
        for (auto child: children) {
            child->UCTScore = double(child->wins) / double(child->plays) + std::sqrt(2.0 * std::log(double(this->plays)) / child->plays);
        }

        return *std::max_element(children.begin(), children.end(), [](Node* a, Node* b) {
            return a->UCTScore < b->UCTScore;
        });
    }

    void update(bool hasWon){
        plays++;

        if(hasWon)
            wins++;
    }

    Node* const getParent() const {
        return parent;
    }

    bool hasChildren(){
        return !children.empty();
    }

    const std::vector<Node *>& getChildren() const {
        return children;
    }

    bool hasUntriedMoves(){
        return !moves.empty();
    }

    unsigned int getPlays() const {
        return plays;
    }

    unsigned int getWins() const {
        return wins;
    }

    const Move& getUntriedMove() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> moves_distribution(0, moves.size() - 1);
        return moves[moves_distribution(gen)];
    }

    const Move& getMove() const {
        return move;
    }

    ~Node() {
        for (auto child: children) {
            delete child;
        }
    }
};


#endif //TDLOG_BOARDGAME_AI_NODE_H
