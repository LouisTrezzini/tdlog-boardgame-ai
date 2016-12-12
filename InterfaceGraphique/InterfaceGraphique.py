# -*- coding: utf-8 -*-

import sys
import ConfigurationDialog
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *

class InterfaceGraphique():
    """ Defines the graphism for the Game. """
    heightMarge = 190
    widthMarge = 100

    def __init__(self, widget, tailleImage, nbRows):
        """ Initialises the graphism for the Game thank to a pre-design widget.
            The class is also composed of the various parameters to
            launch a Party. """

        self.widget = widget

        # Dimensionnement de la fenetre du jeu en fonction des tailleImage
        self.tailleImage = tailleImage
        self.nbRows = nbRows
        self.widthWidget = max(730, tailleImage*nbRows + self.widthMarge)
        self.heightWidget = max(750, tailleImage*nbRows + self.heightMarge)
        self.widget.setMinimumSize(self.widthWidget, self.heightWidget)
        self.widget.setMaximumSize(self.widthWidget, self.heightWidget)
        self.widget.stackedWidget.setMaximumSize(self.widthWidget, self.heightWidget)
        self.widget.rules.setMaximumSize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.rules.move(int(self.widthMarge/2), 50)
        self.widget.Title.setMaximumWidth(self.widthWidget)

        #Affichage du bon stack
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.widget.configureBtn.clicked.connect(self.ConfigurationDialog)
        self.widget.returnBtn.clicked.connect(lambda _ : self.ConfigurationWidget())

        #Sauvegarde des paramètres du jeu
        self.player1 = 0
        self.player2 = 0
        self.plateau = 0

        #Ouverture de boite de dialogues pour la configuration du jeu
        self.configure_dialog = ConfigurationDialog.ConfigureDialog()
        self.widget.show()

    def ConfigurationWidget(self):
        """ Configures the closing of the game when the player clicke
            on the return button """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.plateau.close()
        self.plateau.deleteLater()
        self.plateau = None

    def ConfigurationDialog(self):
        """ Opens several Dialogs to input the information
            for the type of the players. It mades thanks to the
            class ConfigureDialog in the eponym module. """
        self.configure_dialog.initUI()
        self.player1 = self.configure_dialog.player1
        self.player2 = self.configure_dialog.player2
        self.play()

    def play(self):
        """ Launchs the game """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Game)
        self.plateau = Plateau(self.player2, self.player1,
                               self.tailleImage, self.nbRows, self.widget)
        self.plateau.setParent(self.widget.boxGame)
        self.widget.boxGame.setMaximumSize(self.nbRows*self.tailleImage,
                                           self.nbRows*self.tailleImage)
        position  = int((self.widthWidget - self.nbRows*self.tailleImage)/2)
        self.widget.boxGame.move(position, int(self.heightMarge/2))
        self.plateau.show()
        QtCore.QTimer.singleShot(500, self.plateau.play)



class Plateau(QtGui.QWidget):

    def __init__(self, player1, player2, tailleImage, nbRows, parentWidget):
        super(Plateau, self).__init__()

        # Définition du widget parent
        self.parentWidget = parentWidget

        # Création du layout
        self.grid = QtGui.QGridLayout()
        self.grid.setSpacing(0)
        self.setLayout(self.grid)

        #players
        self.player1 = player1
        self.player2 = player2

        #Tailles des Images
        self.tailleImage = tailleImage

        # Création du thème du plateau
        self.themePlateau = ThemePlateau("empty.png", "white.png", "black.png", "waiting.png")
        self.themePlateau.scale(self.tailleImage)

        # Création du jeu
        self.nbRows = nbRows
        self.game = Game(nbRows, player1, player2)
        self.cases = [QtGui.QLabel() for i in range(nbRows ** 2)]

        # Display Number of stones for both palyers:
        self.parentWidget.scorePlayer1.display(self.game.GameState.Board.getBlackStones)
        self.parentWidget.scorePlayer2.display(self.game.GameState.Board.getWhiteStones)

        # Création des boutons
        for i in range(nbRows):
            for j in range(nbRows):
                self.grid.addWidget(self.cases[i + j * nbRows], i, j)
                self.cases[i + j * nbRows].mousePressEvent = lambda x, i = i, j = j: self.change(i, j)
        self.update()

    def play (self):
        if not self.humanTurn():
            self.playTurn()

    def change(self, i, j):
        move = Move(i, j)
        if (Game.isValidMove(self.game.GameState, move)) and self.humanTurn():
            self.game.playMove(move)
            self.update()
            QtCore.QTimer.singleShot(500, self.playTurn)


    def update(self):
        """
        Fonction pour mettre à jour l'affichage du plateau
        et le score des joueurs
        :return:
        """
        for i in range(self.nbRows):
            for j in range(self.nbRows):
                if (self.game.__getitem__(i, j) == Color.WHITE):
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.whitePawnImage)
                if (self.game.__getitem__(i, j) == Color.BLACK):
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.blackPawnImage)
                if (self.game.__getitem__(i, j) == Color.EMPTY):
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.emptySquareImage)
                if (Game.isValidMove(self.game.GameState, Move(i,j))):
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.possibleMoveImage)

        self.parentWidget.scorePlayer1.display(self.game.GameState.Board.getBlackStones)
        self.parentWidget.scorePlayer2.display(self.game.GameState.Board.getWhiteStones)


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
                QtCore.QTimer.singleShot(500, self.playTurn)

    def humanTurn(self):
        """
        Fonction renvoyant true si c'est au tour d'un joueur humain de jouer et false sinon
        :return:
        """
        case1 = self.player1.isHuman() and self.game.GameState.getColorPlaying() == Color.WHITE
        case2 = self.player2.isHuman() and self.game.GameState.getColorPlaying() == Color.BLACK
        return case1 or case2

class ThemePlateau():
    def __init__(self, emptySquareName, whitePawnImageName, blackPawnImageName, possibleMoveImageName):
        self.emptySquareImage = QtGui.QPixmap(emptySquareName)
        self.whitePawnImage = QtGui.QPixmap(whitePawnImageName)
        self.blackPawnImage = QtGui.QPixmap(blackPawnImageName)
        self.possibleMoveImage = QtGui.QPixmap(possibleMoveImageName)
    def scale(self, tailleImages):
        self.emptySquareImage = self.emptySquareImage.scaled(tailleImages, tailleImages)
        self.whitePawnImage = self.whitePawnImage.scaled(tailleImages, tailleImages)
        self.blackPawnImage = self.blackPawnImage.scaled(tailleImages, tailleImages)
        self.possibleMoveImage = self.possibleMoveImage.scaled(tailleImages, tailleImages)


app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")
InterfaceGraphique(widget, 60, 8)
app.exec_()
