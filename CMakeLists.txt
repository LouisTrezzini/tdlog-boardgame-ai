cmake_minimum_required(VERSION 3.5)
project(tdlog-boardgame-ai)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp main.cpp players/IPlayer.h players/RandomPlayer.cpp players/RandomPlayer.h game/Color.h game/Board.cpp game/Board.h game/Grid.h game/Game.cpp game/Game.h game/Move.h game/GameState.h game/Color.cpp)
add_executable(tdlog-boardgame-ai ${SOURCE_FILES})