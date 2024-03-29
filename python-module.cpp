#include "game/Game.h"
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "players/AlphaBetaPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "evaluation/PawnNumberEvaluation.h"
#include "evaluation/MobilityEvaluation.h"
#include "evaluation/PositionEvaluation.h"
#include "evaluation/LinearCombinationEvaluation.h"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;
PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<std::shared_ptr<IEvaluationFunction>>);


PYBIND11_PLUGIN(boardgame_ai_py) {
    py::module m("boardgame_ai_py", "TDLOG Boardgame AI Python binding with pybind11");

    py::bind_vector<std::vector<double>>(m, "DoubleVector");
    py::bind_vector<std::vector<std::shared_ptr<IEvaluationFunction>>>(m, "EvalFctPtrVector");

    py::enum_<Color>(m, "Color")
        .value("WHITE", Color::WHITE)
        .value("BLACK", Color::BLACK)
        .value("EMPTY", Color::EMPTY)
        .export_values()
    ;

    py::class_<IEvaluationFunction, std::shared_ptr<IEvaluationFunction>>(m, "IEvaluationFunction")
        .def("evaluate", &IEvaluationFunction::operator())
    ;

    py::class_<PawnNumberEvaluation, IEvaluationFunction, std::shared_ptr<PawnNumberEvaluation>>(m, "PawnNumberEvaluation")
        .def(py::init<>())
    ;

    py::class_<MobilityEvaluation, IEvaluationFunction, std::shared_ptr<MobilityEvaluation>>(m, "MobilityEvaluation")
        .def(py::init<>())
    ;

    py::class_<PositionEvaluation, IEvaluationFunction, std::shared_ptr<PositionEvaluation>>(m, "PositionEvaluation")
        .def(py::init<>())
    ;

    py::class_<LinearCombinationEvaluation, IEvaluationFunction, std::shared_ptr<LinearCombinationEvaluation>>(m, "LinearCombinationEvaluation")
         .def(py::init<vector<double>, vector<std::shared_ptr<IEvaluationFunction>>>())
    ;

    py::class_<Move>(m, "Move")
        .def(py::init<int, int>())
        .def("passing", &Move::passing)
        .def_property_readonly("x", &Move::getX)
        .def_property_readonly("y", &Move::getY)
    ;

    py::class_<IPlayer>(m, "IPlayer")
        .def("isHuman", &IPlayer::isHuman)
    ;

    py::class_<RandomPlayer, IPlayer>(m, "RandomPlayer")
        .def(py::init<bool>())
        .def("seedGenerator", &RandomPlayer::seedGenerator)
    ;

    py::class_<HumanPlayer, IPlayer>(m, "HumanPlayer")
         .def(py::init<std::string>())
         .def_property_readonly("name", &HumanPlayer::getName)
    ;

    py::class_<MinMaxPlayer, IPlayer>(m, "MinMaxPlayer")
         .def(py::init<std::shared_ptr<IEvaluationFunction>, int, bool>())
    ;

    py::class_<AlphaBetaPlayer, IPlayer>(m, "AlphaBetaPlayer")
         .def(py::init<std::shared_ptr<IEvaluationFunction>, int, bool>())
    ;

    py::class_<MonteCarloTreeSearchPlayer, IPlayer>(m, "MonteCarloTreeSearchPlayer")
        .def(py::init<bool>())
    ;

    py::class_<Board>(m, "Board")
        .def(py::init<int>())
        .def("__str__", &Board::toString)
        .def("getColor", &Board::pieceAt)
        .def(py::self == py::self)
        .def_property_readonly("blackStones", &Board::getBlackStones)
        .def_property_readonly("whiteStones", &Board::getWhiteStones)
    ;

    py::class_<GameState>(m, "GameState")
        .def(py::init<const Board&, Color>())
        // FIXME
        // Ambiguïté car 2 functions getBoard
        .def("getColorPlaying", &GameState::getColorPlaying)
        .def_property_readonly("board", (Board& (GameState::*)()) &GameState::getBoard)
    ;

    py::class_<Game>(m, "Game")
        .def(py::init<int, IPlayer*, IPlayer*>())
        .def("__str__", &Game::toString)
        .def("__getitem__", &Game::pieceAt)
        .def("getLegalMoves", &Game::getLegalMoves)
        .def("getWinner", &Game::getWinner)
        .def("pickMove", &Game::pickMove)
        .def("playMove", &Game::playMove)
        .def("playGame", &Game::playGame)
        .def("playGameWithoutDisplay", &Game::playGameWithoutDisplay)
        .def("isValidMove", &Game::isValidMove)
        .def_property_readonly("gameState", &Game::getGameState)
    ;

    return m.ptr();
}
