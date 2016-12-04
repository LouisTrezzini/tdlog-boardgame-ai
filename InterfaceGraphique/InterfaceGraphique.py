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
                self.cases[i + j * taille].mousePressEvent = lambda x, i = i, j = j: self.change(i, j)

        self.update()
        self.show()
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
        case1 = player1.isHuman() and self.game.GameState.getColorPlaying() == Color.WHITE
        case2 = player2.isHuman() and self.game.GameState.getColorPlaying() == Color.BLACK
        return case1 or case2


app = QtGui.QApplication(sys.argv)
player1 = RandomPlayer()
player2 = HumanPlayer()
Plateau(player1, player2, 8)
app.exec_()
