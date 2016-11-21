#include "game/Game.h"
#include "players/RandomPlayer.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;


PYBIND11_PLUGIN(boardgame_ai_py) {
    py::module m("boardgame_ai_py", "TDLOG Boardgame AI Python binding with pybind11");

    py::enum_<Color>(m, "Color")
        .value("WHITE", Color::WHITE)
        .value("BLACK", Color::BLACK)
        .value("EMPTY", Color::EMPTY)
        .export_values()
    ;

    py::class_<Move>(m, "Move")
        .def(py::init<int, int>())
        .def_property_readonly("x", &Move::getX)
        .def_property_readonly("y", &Move::getY)
    ;

    py::class_<IPlayer>(m, "IPlayer")
    ;

    py::class_<RandomPlayer, IPlayer>(m, "RandomPlayer")
        .def(py::init<>())
    ;

    py::class_<Board>(m, "Board")
        .def(py::init<int>())
        .def("__str__", &Board::toString)
        .def("getColor", &Board::pieceAt)
    ;


    py::class_<GameState>(m, "GameState")
        .def(py::init<const Board&, Color>())
        // FIXME
        // Ambiguïté car 2 fonctions getBoard
        .def_property_readonly("Board", (Board& (GameState::*)()) &GameState::getBoard)
    ;


    py::class_<Game>(m, "Game")
        .def(py::init<int, IPlayer*, IPlayer*>())
        .def("__str__", &Game::toString)
        .def("__getitem__", &Game::pieceAt)
        .def_property_readonly("GameState", &Game::getGameState)
    ;

    return m.ptr();
}
