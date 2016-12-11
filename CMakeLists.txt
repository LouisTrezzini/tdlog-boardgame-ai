cmake_minimum_required(VERSION 3.0)

project(tdlog-boardgame-ai)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES utils/MinMaxOutput.h utils/MinMaxOutput.cpp players/IPlayer.h players/AlphaBetaPlayer.cpp  players/AlphaBetaPlayer.h  players/RandomPlayer.cpp players/RandomPlayer.h game/Color.h game/Board.cpp game/Board.h game/Grid.h game/Game.cpp game/Game.h game/Move.h game/GameState.h game/Color.cpp players/MonteCarloTreeSearchPlayer.cpp players/MonteCarloTreeSearchPlayer.h game/Node.cpp game/Node.h players/HumanPlayer.cpp players/HumanPlayer.h players/MinMaxPlayer.cpp players/MinMaxPlayer.h)
#add_executable(tdlog-boardgame-ai main.cpp ${SOURCE_FILES})

add_subdirectory(pybind11)
pybind11_add_module(boardgame_ai_py python-module.cpp ${SOURCE_FILES})



