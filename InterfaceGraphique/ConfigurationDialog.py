# -*- coding: utf-8 -*-

from PyQt4 import QtGui
from boardgame_ai_py import *
import time as Time

###############################################################################
################ Part : ConfigureDialog #######################################
###############################################################################

class ConfigurationDialog(QtGui.QWidget):
    """ This class launchs several Dialog in which the user can enter
        the information needed to launch the game.
        It reads the size of the Grid, the number of players,
        the number of bots and names of players. """
    def __init__(self):
        """ Initializes a member of the class ConfigureDialog.
            It allows to stocks the value wanted by the player to launch
            a party. So, it is composed of the type of the two player """
        super().__init__()
        self.player1 = None
        self.player2 = None
        self.depth = 0
        self.timeLimit = 0
        self.setGeometry(300, 300, 500, 200)

    def initUI(self):
        """ Launchs several Dialogs in which the user can enter the value wanted
            for the Game. """
        self.setTimeLimit();
        self.player1 = self.createPlayer(self.askPlayerType())
        self.player2 = self.createPlayer(self.askPlayerType())

    def askPlayerType(self):
        """ Launchs a Dialog in which the user can enter the number of
            players wanted. """
        player_types_list = list(["HumanPlayer", "RandomPlayer",
                             "MonteCarloTreeSearchPlayer", "MinMaxPlayer", "AlphaBetaPlayer" ])
        player_type, ok1 = QtGui.QInputDialog.getItem(self, 'Choice of the type of the Player',
                                              'Type of the player :',
                                              player_types_list, editable = False)
        return player_type

    def setDepth(self):
        """ Launchs a Dialog in which the user can enter the force of the AI. """
        force, ok1 = QtGui.QInputDialog.getInt(self, 'Parameters',
                                  'Enter the force of the IA:', min = 1)
        self.depth = int(force)

    def setTimeLimit(self):
        """ Launchs a Dialog in which the user can decide to limit
            the time to play. """
        timesList = list([str(i) for i in range (5, 120, 5)])
        timesList.append("No limit of time")
        time, ok = QtGui.QInputDialog.getItem(self, 'Choice of a the limite of time to play',
                                              'Limit of time to play', timesList, editable = False)
        if time != 'No limit of time':
            time = int(float(time) * 60)  #Time in second
            self.timeLimit = time

    def createPlayer(self, player_type):
        """ Configures the type of player with a string. """
        player_instance = None
        if player_type == "HumanPlayer":
            player_instance = HumanPlayer(self.timeLimit)
        elif player_type == "RandomPlayer":
            player_instance = RandomPlayer(self.timeLimit)

        else :
            self.setDepth()
            if player_type == "MonteCarloTreeSearchPlayer":
                player_instance = MonteCarloTreeSearchPlayer(self.timeLimit)
            if player_type == "MinMaxPlayer":
                player_instance = MinMaxPlayer(PawnNumberEvaluation(), self.depth, self.timeLimit)
            if player_type == "AlphaBetaPlayer":
                player_instance = AlphaBetaPlayer(PawnNumberEvaluation(), self.depth, self.timeLimit)
        return player_instance
