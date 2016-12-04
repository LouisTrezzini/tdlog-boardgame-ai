# -*- coding: utf-8 -*-

from PyQt4 import QtGui

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
        self.setGeometry(300, 300, 290, 150)

    def initUI(self):
        """ Launchs several Dialogs in which the user can enter the value wanted
            for the Game. """
        self.player1 = self.setPlayer()
        self.player2 = self.setPlayer()

    def setPlayer(self):
        """ Launchs a Dialog in which the user can enter the number of
            players wanted. """
        players_list = list(["HumanPlayer", "RandomPlayer", "MonteCarloPlayer"])
        player, ok1 = QtGui.QInputDialog.getItem(self, 'Choice of the type of the Player',
                                              'Type of the player :',
                                              players_list, editable = False)
        return player

    def setDepth(self):
        """ Launchs a Dialog in which the user can enter the force of the AI. """
        force, ok1 = QtGui.QInputDialog.getInt(self, 'Parameters',
                                  'Enter the force of the IA:', min = 1)
        self.depth = int(force)
