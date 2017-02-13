# -*- coding: utf-8 -*-

import sys
import ConfigurationDialog
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *

def secTohms(nb_sec):
     q,s=divmod(nb_sec,60)
     h,m=divmod(q,60)
     return (h,m,s)

def hmsTosec(h,m,s):
    nb_sec = h*3600 + m*60 + s -1
    return nb_sec

def decreaseSec(h,m,s):
    nb_sec = h*3600 + m*60 + s -1
    return secTohms(nb_sec)

class InterfaceGraphique:
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
        self.widget.stackedWidget.resize(self.widthWidget,
                                         self.heightWidget - int(self.heightMarge/2))
        self.widget.stackedWidget.setMaximumSize(self.widthWidget, self.heightWidget)
        self.widget.rules.resize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.rules.setReadOnly(True)
        self.widget.rules.setMaximumSize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.rules.move(int(self.widthMarge/2), 50)
        self.widget.Title.resize(self.widthWidget, 70)
        self.widget.Title.setMaximumWidth(self.widthWidget)
        self.widget.Title.setReadOnly(True)
        positionBtn = int((self.widthWidget-self.widget.configureBtn.frameSize().width())/2)
        self.widget.configureBtn.move(positionBtn, 600)

        #Personnalisation timer:
        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Foreground,QtCore.Qt.red)
        self.widget.timer.setPalette(palette)
        f = QtGui.QFont( "Helvetica", 15)
        f.setBold(True)
        self.widget.timer.setFont(f)

        #Affichage du bon stack
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.widget.configureBtn.clicked.connect(self.OpenConfigurationDialog)
        self.widget.returnBtn.clicked.connect(lambda _ : self.stopGameWidget())

        #Sauvegarde des paramètres du jeu
        self.timeLimit = None
        self.player1 = None
        self.player2 = None
        self.plateau = None

        #Ouverture de boite de dialogues pour la configuration du jeu
        self.configure_dialog = ConfigurationDialog.ConfigurationDialog()
        self.widget.show()

    def stopGameWidget(self):
        """ Configures the closing of the game when the player clicks
            on the return button """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.plateau.close()
        self.plateau.deleteLater()
        self.plateau = None

    def OpenConfigurationDialog(self):
        """ Opens several Dialogs to input the information
            for the type of the players. It mades thanks to the
            class ConfigurationDialog in the eponym module. """
        self.configure_dialog.initUI()
        self.player1 = self.configure_dialog.player1
        self.player2 = self.configure_dialog.player2
        self.timeLimit = self.configure_dialog.timeLimit
        self.play()

    def play(self):
        """ Launchs the game """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Game)
        self.plateau = Plateau(self.player2, self.player1, self.timeLimit,
                               self.tailleImage, self.nbRows, self.widget)
        self.plateau.setParent(self.widget.boxGame)
        # Si on enlève le + 1, la taille est trop petite
        self.widget.boxGame.resize((self.nbRows + 1)*self.tailleImage,
                                   (self.nbRows + 1)*self.tailleImage)

        position  = int((self.widthWidget - self.nbRows*self.tailleImage)/2)
        self.widget.boxGame.move(position, int(self.heightMarge/2))
        self.plateau.show()
        QtCore.QTimer.singleShot(500, self.plateau.play)

class Timer (QtCore.QTimer):
    """ Represents a Timer that indicates the times that remains
        to play. """

    def __init__(self, time, widget):
        # Initialize the timer
        super().__init__()
        self.widget = widget
        self.time = time

    def timerEvent(self, event):
        self.time = decreaseSec(self.time[0],self.time[1],self.time[2])
        nb_sec = hmsTosec(self.time[0],self.time[1],self.time[2])
        strTime = '{:2.0f}:{:2.0f}:{:2.0f}'.format(self.time[0],self.time[1], self.time[2])
        self.widget.timer.setText(strTime)


class Plateau(QtGui.QWidget):
    def __init__(self, player1, player2, timeLimit, tailleImage, nbRows, Widget):
        super(Plateau, self).__init__()

        # Définition du widget parent
        self.widget = Widget

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
        self.widget.scorePlayer1.display(self.game.gameState.board.blackStones)
        self.widget.scorePlayer2.display(self.game.gameState.board.whiteStones)

        #Display Timer:
        self.timeRemainingCurrentPlayer = secTohms(self.player1.timeRemainingToPlay)
        self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.widget)
        self.timerCurrentPlayer.startTimer(1000)


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
        if Game.isValidMove(self.game.gameState, move) and self.humanTurn():
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
                if self.game.__getitem__(i, j) == Color.WHITE:
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.whitePawnImage)
                if self.game.__getitem__(i, j) == Color.BLACK:
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.blackPawnImage)
                if self.game.__getitem__(i, j) == Color.EMPTY:
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.emptySquareImage)
                if Game.isValidMove(self.game.gameState, Move(i,j)):
                    self.cases[i + j * self.nbRows].setPixmap(self.themePlateau.possibleMoveImage)

        self.widget.scorePlayer1.display(self.game.gameState.board.blackStones)
        self.widget.scorePlayer2.display(self.game.gameState.board.whiteStones)

        if self.game.gameState.getColorPlaying() == Color.BLACK :
            self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
            self.timeRemainingCurrentPlayer = secTohms(self.player1.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.widget)
            self.timerCurrentPlayer.startTimer(1000)
        else :
            self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
            self.timeRemainingCurrentPlayer = secTohms(self.player2.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.widget)
            self.timerCurrentPlayer.startTimer(1000)

    def playTurn(self):
        """
        Fonction pour jouer un tour
        :return:
        """
        if Game.getWinner(self.game.gameState) != Color.EMPTY:
            return

        if not self.humanTurn():
            pickedMove = self.game.pickMove(self.game.gameState)
            self.game.playMove(pickedMove)
            self.update()
            if not self.humanTurn():
                QtCore.QTimer.singleShot(500, self.playTurn)

    def humanTurn(self):
        """
        Fonction renvoyant true si c'est au tour d'un joueur humain de jouer et false sinon
        :return:
        """
        case1 = self.player1.isHuman() and self.game.gameState.getColorPlaying() == Color.WHITE
        case2 = self.player2.isHuman() and self.game.gameState.getColorPlaying() == Color.BLACK
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
