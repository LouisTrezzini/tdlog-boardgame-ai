cmake_minimum_required(VERSION 3.0)

project(tdlog-boardgame-ai)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EVALUATION_FILES
        evaluation/IEvaluationFunction.h
        evaluation/EndGameEvaluation.cpp
        evaluation/EndGameEvaluation.h
        evaluation/LinearCombinationEvaluation.cpp
        evaluation/LinearCombinationEvaluation.h
        evaluation/LinearCombinationOverTimeEvaluation.cpp
        evaluation/LinearCombinationOverTimeEvaluation.h
        evaluation/PawnNumberEvaluation.cpp
        evaluation/PawnNumberEvaluation.h
        evaluation/PositionEvaluation.cpp
        evaluation/PositionEvaluation.h
        evaluation/MobilityEvaluation.cpp
        evaluation/MobilityEvaluation.h
        )
set(PLAYER_FILES
        players/GeneticalAlgorithm.h
        players/HumanPlayer.cpp
        players/HumanPlayer.h
        players/IPlayer.h
        players/MinMaxPlayer.cpp
        players/MinMaxPlayer.h
        players/MonteCarloTreeSearchPlayer.cpp
        players/MonteCarloTreeSearchPlayer.h
        players/RandomPlayer.cpp
        players/RandomPlayer.h
        players/AlphaBetaPlayer.cpp
        players/AlphaBetaPlayer.h
        players/Statistics.cpp
        players/Statistics.h
        )
set(GAME_FILES
        game/Board.cpp
        game/Board.h
        game/Color.cpp
        game/Color.h
        game/Game.cpp
        game/Game.h
        game/GameState.h
        game/Grid.h
        game/Move.h
        game/Node.cpp
        game/Node.h
        )
set(UTILS_FILES
        utils/MinMaxOutput.h
        utils/MinMaxOutput.cpp
        )

set(SOURCE_FILES ${EVALUATION_FILES} ${PLAYER_FILES} ${GAME_FILES} ${UTILS_FILES})

add_executable(tdlog-boardgame-ai main.cpp ${SOURCE_FILES})
target_link_libraries(tdlog-boardgame-ai pthread)


add_subdirectory(pybind11)
pybind11_add_module(boardgame_ai_py python-module.cpp ${SOURCE_FILES})
target_link_libraries(boardgame_ai_py pthread)
