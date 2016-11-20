#include <boost/python.hpp>

#include "game/Game.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(boardgame)
{

    enum_<Color>("Color")
            .value("WHITE", Color::WHITE)
            .value("BLACK", Color::BLACK)
            .value("EMPTY", Color::EMPTY)
            .export_values()
            ;


    class_<Board>("Board", init<int>())
            .def("__str__", &Board::toString)
            .def("getColor", &Board::pieceAt)
            ;

    class_<GameState>("GameState", init<const Board&, Color>())
            .add_property("Board", make_function(&GameState::getBoard, return_internal_reference<>()))
            ;

    class_<Game>("Game", init<int, IPlayer*, IPlayer*>())
            .def("__str__", &Game::toString)
            .def("__getitem__", &Game::pieceAt)
            .add_property("GameState", make_function(&Game::getGameState, return_internal_reference<>()))
            ;

};
