#include <iostream>
#include "players/RandomPlayer.h"
#include "players/HumanPlayer.h"
#include "players/MonteCarloTreeSearchPlayer.h"
#include "game/Game.h"

#include <boost/python.hpp>

using namespace boost::python;

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_boardgame
extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initboardgame
    extern "C" void INIT_MODULE();
#endif

int main(int argc, char *argv[]) {
    RandomPlayer whitePlayer;
    RandomPlayer blackPlayer;

    Game game(8, &whitePlayer, &blackPlayer);

    object main_module, boardgame_module;
    dict main_namespace;


    // FIXME
//    try {
        PyImport_AppendInittab((char*)"boardgame", INIT_MODULE);
        Py_Initialize();
        main_module = import("__main__");
        main_namespace = extract<dict>(main_module.attr("__dict__"));
        // Que fait cette ligne ?
        boardgame_module = import("boardgame");

        main_namespace["game"] = game;

        exec_file("gui/main.py", main_namespace);
//    } catch (error_already_set& e) {
//        PyErr_PrintEx(0);
//        return 1;
//    }

    game.playGame();

    std::cout << game.getWinner(game.getGameState()) << std::endl;

    main_namespace["game"] = game;
    // Deuxième exécution
    exec_file("gui/main.py", main_namespace);

    return 0;
}
