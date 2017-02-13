# -*- coding: utf-8 -*-

import sys
import DataBaseHandler
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *
import Timer

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
        if self.player1.timeRemainingToPlay > 0:
            self.timeRemainingCurrentPlayer = Timer.secTohms(self.player1.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer.Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
            self.timerCurrentPlayer.startTimer(1000)
        else :
            self.timeRemainingCurrentPlayer = Timer.secTohms(self.player1.timeRemainingToPlay)
            self.timerCurrentPlayer = Timer.Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)

        # Création des boutons
        for i in range(nbRows):
            for j in range(nbRows):
                self.grid.addWidget(self.cases[i + j * nbRows], i, j)
                self.cases[i + j * nbRows].mousePressEvent = lambda x, i = i, j = j: self.change(i, j)
        self.updateCase()

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
            self.updateCase()
            QtCore.QTimer.singleShot(100, self.playTurn)


    def updateCase(self):
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

    def updateTime(self):
        """
        Fonction pour mettre à jour l'affichage du plateau
        et le temps restant aux joueurs
        :return:
        """
        if self.player1.timeRemainingToPlay > 0:

            if self.game.gameState.getColorPlaying() == Color.BLACK :
                self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
                self.player2.setTimeRemainingToPlay(Timer.hmsTosec(self.timerCurrentPlayer.time[0],
                                                                   self.timerCurrentPlayer.time[1],
                                                                   self.timerCurrentPlayer.time[2]))
                self.timeRemainingCurrentPlayer = Timer.secTohms(self.player1.timeRemainingToPlay)
                self.timerCurrentPlayer = Timer.Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
                self.timerCurrentPlayer.startTimer(1000)

            else :
                self.timerCurrentPlayer.killTimer(self.timerCurrentPlayer.timerId())
                self.player1.setTimeRemainingToPlay(Timer.hmsTosec(self.timerCurrentPlayer.time[0],
                                                                   self.timerCurrentPlayer.time[1],
                                                                   self.timerCurrentPlayer.time[2]))
                self.timeRemainingCurrentPlayer = Timer.secTohms(self.player2.timeRemainingToPlay)
                self.timerCurrentPlayer = Timer.Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)
                self.timerCurrentPlayer.startTimer(1000)

        else :

            self.timerCurrentPlayer = Timer.Timer(self.timeRemainingCurrentPlayer, self.displayScoreWidget)

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

        self.updateCase()
        self.updateTime()

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
            self.updateCase()
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
