# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, uic
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


        for i in range(taille):
            for j in range(taille):
                pix = QtGui.QPixmap("noir.png")
                pix = pix.scaled(50, 50)
                self.cases[i + j * taille].setPixmap(pix)
                self.grid.addWidget(self.cases[i + j * taille], i, j)
                self.cases[i + j * taille].mousePressEvent = lambda x, k = self.cases[i + j * taille]: self.change(k)

        self.show()

    def change(self, label):
        pix = QtGui.QPixmap("white.png")
        pix = pix.scaled(50, 50)
        label.setPixmap(pix)




app = QtGui.QApplication(sys.argv)
player1 = RandomPlayer()
player2 = HumanPlayer()
Plateau(player1, player2, 8)
app.exec_()