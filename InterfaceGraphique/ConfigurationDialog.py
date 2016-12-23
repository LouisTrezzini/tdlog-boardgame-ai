# -*- coding: utf-8 -*-

from PyQt4 import QtGui
from boardgame_ai_py import *

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
        self.setGeometry(300, 300, 500, 200)

    def initUI(self):
        """ Launchs several Dialogs in which the user can enter the value wanted
            for the Game. """
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

    def createPlayer(self, player_type):
        """ Configures the type of player with a string. """
        player_instance = None
        if player_type == "HumanPlayer":
            player_instance = HumanPlayer()
        if player_type == "RandomPlayer":
            player_instance = RandomPlayer()
        if player_type == "MonteCarloTreeSearchPlayer":
            player_instance = MonteCarloTreeSearchPlayer()
        if player_type == "MinMaxPlayer":
            # FIXME
            # Donner le choix à l'utilisateur
            player_instance = MinMaxPlayer(PawnNumberEvaluation(), 3)
        if player_type == "AlphaBetaPlayer":
            # FIXME
            # Donner le choix à l'utilisateur
            player_instance = AlphaBetaPlayer(PawnNumberEvaluation(), 7)
        return player_instance

