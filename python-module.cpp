#include <boost/python.hpp>

#include "game/Game.h"
#include "game/Board.h"

using namespace boost::python;

const GameState& Game_GameState(Game& self)
{
   return self.getGameState();
};

BOOST_PYTHON_MODULE(boardgame)
{
    class_<Board>("Board", init<int>())
            .def("__str__", &Board::toString)
            .def("getColor", &Board::pieceAt)
            ;

    class_<GameState>("GameState", init<const Board&, Color>())
            .add_property("Board", make_function(&GameState::getBoard, return_internal_reference<>()))
            ;

    class_<Game>("Game", init<int, IPlayer*, IPlayer*>())
            .def("__str__", &Game::toString)
            .add_property("GameState", make_function(&Game::getGameState, return_internal_reference<>()))
            ;

};
