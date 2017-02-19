# -*- coding: utf-8 -*-

from PyQt4 import QtGui
from boardgame_ai_py import *
import time as Time
import DataBaseHandler

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

    def askPlayerName(self):
        """ Launchs a Dialog in which the user can enter his pseudo. """
        player_name, ok1 = QtGui.QInputDialog.getText(self,'Choice of the name of the Player','Enter your pseudo :',QtGui.QLineEdit.Normal)
        return player_name

    def askPlayerPassword(self):
        """ Launchs a Dialog in which the user can enter his password. """
        player_password, ok1 = QtGui.QInputDialog.getText(self,'Welcome','Enter your password :',QtGui.QLineEdit.Normal)
        return player_password

    # TODO fix it
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
                                              'Limit of time to play',
                                              timesList, editable = False)
        if time != 'No limit of time':
            time = int(float(time) * 60)  #Time in second
            self.timeLimit = time
        else :
            self.timeLimit = -1

    def createPlayer(self, player_type):
        """ Configures the type of player with a string. """
        player_instance = None
        if player_type == "HumanPlayer":
            data = DataBaseHandler.StatisticsDataBaseController()
            access = DataBaseHandler.PasswordsDataBaseController()
            name = self.askPlayerName()
            password = self.askPlayerPassword()
            while (access.checkAccess(name,password,data) == False):
                print("wrong password")
                password = self.askPlayerPassword()
            player_instance = HumanPlayer(name, self.timeLimit)
            data.close()
            access.close()
        elif player_type == "RandomPlayer":
            player_instance = RandomPlayer(True, self.timeLimit)
        elif player_type == "MonteCarloTreeSearchPlayer":
            self.setDepth()
            player_instance = MonteCarloTreeSearchPlayer(True, self.timeLimit)
        elif player_type == "MinMaxPlayer":
            self.setDepth()
            # FIXME
            # Donner le choix à l'utilisateur
            player_instance = MinMaxPlayer(PawnNumberEvaluation(), self.depth, True, self.timeLimit)
        elif player_type == "AlphaBetaPlayer":
            self.setDepth()
            # FIXME
            # Donner le choix à l'utilisateur
            player_instance = AlphaBetaPlayer(PawnNumberEvaluation(), self.depth, True, self.timeLimit)

        return player_instance
