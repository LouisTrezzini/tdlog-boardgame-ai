#include <boost/python.hpp>

#include "game/Game.h"
#include "game/Board.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(boardgame)
{
    class_<Board>("Board", init<int>())
            .def("__str__", &Board::toString)
            ;

    class_<Game>("Game", init<int, IPlayer*, IPlayer*>())
            .def("__str__", &Game::toString)
            ;
};