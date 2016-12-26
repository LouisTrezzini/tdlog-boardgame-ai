#ifndef TDLOG_BOARDGAME_AI_STATISTICS_H
#define TDLOG_BOARDGAME_AI_STATISTICS_H

#include "IPlayer.h"
#include "../game/Move.h"
#include "../game/GameState.h"

//TODO A deplacer (dans utilis ?) ou trouver ne librairie qu le fait

double mean(std::vector<double> vec);
double standardDeviation(std::vector<double> vec);

void LoiDesGainsSurXParties(int nbGame, IPlayer *player1, int sizeGrid = 8);y

#endif //TDLOG_BOARDGAME_AI_STATISTICS_H
