# -*- coding: utf-8 -*-

from PyQt4 import QtGui
from boardgame_ai_py import *

playerType = list(["HumanPlayer", "RandomPlayer",
                   "MonteCarloTreeSearchPlayer", "MinMaxPlayer",
                   "GeneticalPlayer" ])

###############################################################################
################ Part : ConfigureDialog #######################################
###############################################################################

class ConfigureDialog(QtGui.QWidget):
    """ This class launchs several Dialog in which the user can enter
        the information needed to launch the game.
        It reads the size of the Grid, the number of players,
        the number of bots and names of players. """
    def __init__(self):
        """ Initializes a member of the class ConfigureDialog.
            It allows to stocks the value wanted by the player to launch
            a party. So, it is composed of the type of the two player """
        super().__init__()
        self.player1 = 0
        self.player2 = 0
        self.depth = 0
        self.setGeometry(300, 300, 500, 200)

    def initUI(self):
        """ Launchs several Dialogs in which the user can enter the value wanted
            for the Game. """
        self.player1 = self.setPlayer()
        self.player2 = self.setPlayer()
        self.realTypeOfPlayer(str(self.player1), 1)
        self.realTypeOfPlayer(str(self.player2), 2)

    def setPlayer(self):
        """ Launchs a Dialog in which the user can enter the number of
            players wanted. """
        players_list = playerType
        player, ok1 = QtGui.QInputDialog.getItem(self, 'Choice of the type of the Player',
                                              'Type of the player :',
                                              players_list, editable = False)
        return player

    def setDepth(self):
        """ Launchs a Dialog in which the user can enter the force of the AI. """
        force, ok1 = QtGui.QInputDialog.getInt(self, 'Parameters',
                                  'Enter the force of the IA:', min = 1)
        self.depth = int(force)

    def realTypeOfPlayer(self, string, number_of_player):
        """ Configures the type of player with a string. """
        player_type = 0
        if string == playerType[0] :
            player_type = HumanPlayer()
        if string == playerType[1] :
            player_type = RandomPlayer()
        if string == playerType[2] :
            player_type = MonteCarloTreeSearchPlayer()
        if string == playerType[3]:
            eval = PawnNumberEvaluation()
            player_type = MinMaxPlayer(eval)
        if string == playerType[4]:
            player_type = GeneticalPlayer()
        if number_of_player == 1:
            self.player1 = player_type
        if number_of_player == 2:
            self.player2 = player_type
