//
// Created by till034 on 10/15/16.
//

#ifndef TDLOG_BOARDGAME_AI_GAMESTATE_H
#define TDLOG_BOARDGAME_AI_GAMESTATE_H


#include "Board.h"

class GameState {
    Board board;
    Color colorPlaying;

public:
    GameState(const Board& board, Color colorPlaying) : board(board), colorPlaying(colorPlaying) { };

    const Board& getBoard() const {
        return board;
    }

    Color getColorPlaying() const {
        return colorPlaying;
    }
};


#endif //TDLOG_BOARDGAME_AI_GAMESTATE_H
