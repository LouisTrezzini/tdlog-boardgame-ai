# -*- coding: utf-8 -*-

import sys
import time
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *


class InterfaceGraphique(QtGui.QWidget):
    def __init__(self):
        super(InterfaceGraphique, self).__init__()
        self.widget = uic.loadUi("mainwindow.ui")

        self.widget.RulesButton.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_2))
        self.widget.RulesButtonTab3.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_2))
        self.widget.RulesButtonTab4.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_2))
        self.widget.RulesButtonTab5.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_2))

        self.widget.ComeBackButtonTab3.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab))
        self.widget.ComeBackButtonTab4.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab))
        self.widget.ComeBackButtonTab5.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab))
        self.widget.playButton.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab))

        self.widget.TwoPlayersButton.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_3))
        self.widget.OnePlayerButton.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_4))
        self.widget.ZeroPlayerButton.clicked.connect(lambda _ : self.widget.tabWidget.setCurrentWidget(self.widget.tab_5))

        self.widget.show()

class Plateau(QtGui.QWidget):
    # Constante de classe
    tailleImage = 80

    def __init__(self, player1, player2, taille):
        super(Plateau, self).__init__()

        # Création du layout
        self.grid = QtGui.QGridLayout()
        self.grid.setSpacing(0)
        self.setLayout(self.grid)

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
                self.cases[i + j * taille].mousePressEvent = lambda x, k = self.cases[i + j * taille]: self.change(k)

        self.update()
        self.show()
        self.playTurn()

    def change(self, label):
        pix = QtGui.QPixmap("white.png")
        pix = pix.scaled(self.tailleImage, self.tailleImage)
        #label.setPixmap(pix)


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

        pickedMove = self.game.pickMove(self.game.GameState)
        self.game.playMove(pickedMove)
        self.update()

        # On rappelle la fonction au bout d'un certain nombre de millisecondes
        QtCore.QTimer.singleShot(1, self.playTurn)







app = QtGui.QApplication(sys.argv)
player1 = RandomPlayer()
player2 = RandomPlayer()
Plateau(player1, player2, 8)
app.exec_()
