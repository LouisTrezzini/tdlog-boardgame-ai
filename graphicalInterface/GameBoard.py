# -*- coding: utf-8 -*-

import sys
import DataBaseHandler
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

class GameBoard(QtGui.QWidget):

    def __init__(self, player1, player2, sizeImage, nbRows, displayScoreWidget):
        super(GameBoard, self).__init__()

        # Définition du widget parent
        self.displayScoreWidget = displayScoreWidget

        # Création du layout
        self.grid = QtGui.QGridLayout()
        self.grid.setSpacing(0)
        self.setLayout(self.grid)

        # Joueurs
        self.player1 = player1
        self.player2 = player2

        # Tailles des Images
        self.sizeImage = sizeImage

        # Création du thème du plateau
        self.gameBoardTheme = GameBoardTheme("empty.png", "white.png", "black.png", "waiting.png")
        self.gameBoardTheme.scale(self.sizeImage)

        # Création du jeu
        self.nbRows = nbRows
        self.game = Game(nbRows, player1, player2)
        self.cases = [QtGui.QLabel() for i in range(nbRows ** 2)]

        # Affichage des nombres de pions pour chaque joueur
        self.displayScoreWidget.scorePlayer1.display(self.game.gameState.board.blackStones)
        self.displayScoreWidget.scorePlayer2.display(self.game.gameState.board.whiteStones)

        #Display Timer:
        self.timeRemainingCurrentPlayer = secTohms(self.player1.timeRemainingToPlay)
        self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
        self.timerCurrentPlayer.startTimer(1000)

        # Création des boutons
        for i in range(nbRows):
            for j in range(nbRows):
                self.grid.addWidget(self.cases[i + j * nbRows], i, j)
                self.cases[i + j * nbRows].mousePressEvent = lambda x, i = i, j = j: self.change(i, j)
        self.update()

    def change(self, i, j):
        """
        Applique le changement correspondant au pion en (i,j)
        :param i:
        :param j:
        :return:
        """
        move = Move(i, j)
        if Game.isValidMove(self.game.gameState, move) and self.humanTurn():
            self.game.playMove(move)
            self.update()
            QtCore.QTimer.singleShot(100, self.playTurn)


    def update(self):
        """
        Fonction pour mettre à jour l'affichage du plateau
        et le score des joueurs
        :return:
        """
        for i in range(self.nbRows):
            for j in range(self.nbRows):
                if self.game.__getitem__(i, j) == Color.WHITE:
                    self.cases[i + j * self.nbRows].setPixmap(self.gameBoardTheme.whitePawnImage)
                if self.game.__getitem__(i, j) == Color.BLACK:
                    self.cases[i + j * self.nbRows].setPixmap(self.gameBoardTheme.blackPawnImage)
                if self.game.__getitem__(i, j) == Color.EMPTY:
                    self.cases[i + j * self.nbRows].setPixmap(self.gameBoardTheme.emptySquareImage)
                if Game.isValidMove(self.game.gameState, Move(i,j)):
                    self.cases[i + j * self.nbRows].setPixmap(self.gameBoardTheme.possibleMoveImage)

        self.displayScoreWidget.scorePlayer1.display(self.game.gameState.board.blackStones)
        self.displayScoreWidget.scorePlayer2.display(self.game.gameState.board.whiteStones)

        if self.game.gameState.getColorPlaying() == Color.BLACK :
            self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
            self.timeRemainingCurrentPlayer = secTohms(self.player1.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
            self.timerCurrentPlayer.startTimer(1000)
        else :
            self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
            self.timeRemainingCurrentPlayer = secTohms(self.player2.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
            self.timerCurrentPlayer.startTimer(1000)

    def playTurn(self):
        """
        Fonction pour jouer un tour
        :return:
        """
        if Game.getWinner(self.game.gameState) != Color.EMPTY:
            data = DataBaseHandler.StatisticsDataBaseController()
            data.actualise(self.player1, self.player2, self.game.gameState.board.whiteStones,self.nbRows)
            data.actualise(self.player2, self.player1, self.game.gameState.board.blackStones,self.nbRows)
            data.close()
            return

        if not self.humanTurn():
            pickedMove = self.game.pickMove(self.game.gameState)
            self.game.playMove(pickedMove)
            QtCore.QTimer.singleShot(200, self.playTurn)

        self.update()

    def humanTurn(self):
        """
        Fonction renvoyant true si c'est au tour d'un joueur humain de jouer et false sinon
        :return:
        """
        case1 = self.player1.isHuman() and self.game.gameState.getColorPlaying() == Color.WHITE
        case2 = self.player2.isHuman() and self.game.gameState.getColorPlaying() == Color.BLACK

        # Fait passer le joueur humain automatiquement s'il n'a aucun coup
        cannotPlay = Move.passing()
        if (case1 or case2) and Game.isValidMove(self.game.gameState, cannotPlay):
            self.game.playMove(cannotPlay)
            self.update()
            case1 = self.player1.isHuman() and self.game.gameState.getColorPlaying() == Color.WHITE
            case2 = self.player2.isHuman() and self.game.gameState.getColorPlaying() == Color.BLACK
            return case1 or case2
        return case1 or case2


class GameBoardTheme():
    """
    Classe permettant de définir différents thèmes pour le jeu
    """
    def __init__(self, emptySquareName, whitePawnImageName, blackPawnImageName, possibleMoveImageName):
        self.emptySquareImage = QtGui.QPixmap(emptySquareName)
        self.whitePawnImage = QtGui.QPixmap(whitePawnImageName)
        self.blackPawnImage = QtGui.QPixmap(blackPawnImageName)
        self.possibleMoveImage = QtGui.QPixmap(possibleMoveImageName)
    def scale(self, sizeImages):
        self.emptySquareImage = self.emptySquareImage.scaled(sizeImages, sizeImages)
        self.whitePawnImage = self.whitePawnImage.scaled(sizeImages, sizeImages)
        self.blackPawnImage = self.blackPawnImage.scaled(sizeImages, sizeImages)
        self.possibleMoveImage = self.possibleMoveImage.scaled(sizeImages, sizeImages)
