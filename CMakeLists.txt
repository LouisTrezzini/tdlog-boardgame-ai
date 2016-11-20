cmake_minimum_required(VERSION 3.0)

project(tdlog-boardgame-ai)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp python-module.cpp players/IPlayer.h players/RandomPlayer.cpp players/RandomPlayer.h game/Color.h game/Board.cpp game/Board.h game/Grid.h game/Game.cpp game/Game.h game/Move.h game/GameState.h game/Color.cpp players/MonteCarloTreeSearchPlayer.cpp players/MonteCarloTreeSearchPlayer.h game/Node.cpp game/Node.h players/HumanPlayer.cpp players/HumanPlayer.h)
add_executable(tdlog-boardgame-ai ${SOURCE_FILES})

find_package( PythonLibs 3.5 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )
target_link_libraries(tdlog-boardgame-ai ${PYTHON_LIBRARIES})

find_package( Boost COMPONENTS python-py35 REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
target_link_libraries(tdlog-boardgame-ai ${Boost_LIBRARIES})


PYTHON_ADD_MODULE(boardgame python-module.cpp)



