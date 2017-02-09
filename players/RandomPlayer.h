#ifndef TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
#define TDLOG_BOARDGAME_AI_RANDOMPLAYER_H

#include <cstdlib>

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <random>
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <chrono>
#include <utility>

/*
 * A random Othello player that chooses random legal moves
 */
class RandomPlayer : public IPlayer {
    static std::mt19937 generator;

public:
    RandomPlayer();

    virtual Move getAction(const GameState& gameState) const;

    virtual ~RandomPlayer();

    static void seedGenerator(int seed);
};


#endif //TDLOG_BOARDGAME_AI_RANDOMPLAYER_H
