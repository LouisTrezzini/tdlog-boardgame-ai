# -*- coding: utf-8 -*-

import sys
import ConfigurationDialog
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *

class InterfaceGraphique():
    """ Defines the graphism for the Game. """

    def __init__(self, wiget):
        """ Initialises the graphism for the Game thank to a pre-design widget.
            The class is also composed of the various parameters to
            launch a Party. """

        self.widget = widget
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.widget.configureBtn.clicked.connect(self.ConfigurationDialog)
        self.widget.returnBtn.clicked.connect(lambda _ : self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration))
        self.player1 = 0
        self.player2 = 0
        self.plateau = 0
        self.configure_dialog = ConfigurationDialog.ConfigureDialog()
        self.widget.show()

    def realTypeOfPlayer(self, string, number_of_player):
        """ Configures the type of player with a string. """
        if string == "HumanPlayer":
            print('ok')
            player_type = HumanPlayer()
        if string == "RandomPlayer":
            player_type = RandomPlayer()
        if string == "MonteCarloPlayer":
            player_type = MonteCarloPlayer()
        if number_of_player == 1:
            self.player1 = player_type
        if number_of_player == 2:
            self.player2 = player_type

    def ConfigurationDialog(self):
        """ Opens several Dialogs to input the information
            for the type of the players. It mades thanks to the
            class ConfigureDialog in the eponym module. """
        self.configure_dialog.initUI()
        self.realTypeOfPlayer(self.configure_dialog.player1, 1)
        self.realTypeOfPlayer(self.configure_dialog.player2, 2)
        self.play()

    def play(self):
        """ Launchs the game """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Game)
        self.plateau = Plateau(self.player1, self.player2, 8)
        self.widget.boxGame.addWidget(self.plateau)
        self.plateau.play()



class Plateau(QtGui.QWidget):
    # Constante de classe
    tailleImage = 80

    def __init__(self, player1, player2, taille):
        super(Plateau, self).__init__()

        # Création du layout
        self.grid = QtGui.QGridLayout()
        self.grid.setSpacing(0)
        self.setLayout(self.grid)

        #players
        self.player1 = player1
        self.player2 = player2

        # Création du jeu
        self.taille = taille
        self.game = Game(taille, player1, player2)
        self.cases = [QtGui.QLabel() for i in range(taille ** 2)]

        # Création des boutons
        for i in range(taille):
            for j in range(taille):
                pix = QtGui.QPixmap("vide.png")
                pix = pix.scaled(self.tailleImage, self.tailleImage)
                self.cases[i + j * taille].setPixmap(pix)
                self.grid.addWidget(self.cases[i + j * taille], i, j)
                self.cases[i + j * taille].mousePressEvent = lambda x, i = i, j = j: self.change(i, j)
        self.update()
        self.show()

    def play (self):
        if not self.humanTurn():
            self.playTurn()

    def change(self, i, j):
        move = Move(i, j)
        if (Game.isValidMove(self.game.GameState, move)) and self.humanTurn():
            self.game.playMove(move)
            self.update()
            QtCore.QTimer.singleShot(1000, self.playTurn)


    def update(self):
        """
        Fonction pour mettre à jour l'affichage du plateau
        :return:
        """
        for i in range(self.taille):
            for j in range(self.taille):
                if (self.game.__getitem__(i, j) == Color.WHITE):
                    pix = QtGui.QPixmap("white.png")
                    pix = pix.scaled(self.tailleImage, self.tailleImage)
                    self.cases[i + j * self.taille].setPixmap(pix)
                if (self.game.__getitem__(i, j) == Color.BLACK):
                    pix = QtGui.QPixmap("black.png")
                    pix = pix.scaled(self.tailleImage, self.tailleImage)
                    self.cases[i + j * self.taille].setPixmap(pix)
                if (self.game.__getitem__(i, j) == Color.EMPTY):
                    pix = QtGui.QPixmap("empty.png")
                    pix = pix.scaled(self.tailleImage, self.tailleImage)
                    self.cases[i + j * self.taille].setPixmap(pix)

    def playTurn(self):
        """
        Fonction pour jouer un tour
        :return:
        """
        if (Game.getWinner(self.game.GameState) != Color.EMPTY):
            return

        if not self.humanTurn():
            pickedMove = self.game.pickMove(self.game.GameState)
            self.game.playMove(pickedMove)
            self.update()
            if not self.humanTurn():
                QtCore.QTimer.singleShot(1000, self.playTurn)

    def humanTurn(self):
        """
        Fonction renvoyant true si c'est au tour d'un joueur humain de jouer et false sinon
        :return:
        """
        case1 = self.player1.isHuman() and self.game.GameState.getColorPlaying() == Color.WHITE
        case2 = self.player2.isHuman() and self.game.GameState.getColorPlaying() == Color.BLACK
        return case1 or case2


app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")
InterfaceGraphique(widget)
app.exec_()
