# -*- coding: utf-8 -*-

import sys
import ConfigurationDialog
import DataBaseHandler
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *



class GraphicInterface:

    """ Defines the graphism for the Game. """
    heightMarge = 190
    widthMarge = 100

    def __init__(self, widget, sizeImage, nbRows):
        """ Initialises the graphism for the Game thank to a pre-design widget.
            The class is also composed of the various parameters to
            launch a Party. """

        self.widget = widget

        # Dimensionnement de la fenêtre du jeu en fonction de sizeImage
        self.sizeImage = sizeImage
        self.nbRows = nbRows
        self.widthWidget = max(730, sizeImage*nbRows + self.widthMarge)
        self.heightWidget = max(750, sizeImage*nbRows + self.heightMarge)
        self.widget.setMinimumSize(self.widthWidget, self.heightWidget)
        self.widget.setMaximumSize(self.widthWidget, self.heightWidget)
        self.widget.stackedWidget.resize(self.widthWidget,
                                         self.heightWidget - int(self.heightMarge/2))
        self.widget.stackedWidget.setMaximumSize(self.widthWidget, self.heightWidget)
        self.widget.rules.resize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.rules.setMaximumSize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.rules.move(int(self.widthMarge/2), 50)
        self.widget.Title.resize(self.widthWidget, 70)
        self.widget.Title.setMaximumWidth(self.widthWidget)
        self.widget.Title.setReadOnly(True)
        positionBtn = int((self.widthWidget-self.widget.configureBtn.frameSize().width())/2)
        self.widget.configureBtn.move(positionBtn, 580)
        self.widget.statisticsBtn.move(positionBtn, 610)
        
        # Dimensionnement de la table des statistiques
        self.widget.tableWidget.setMaximumSize(self.widthWidget - self.widthMarge,
                                         self.heightWidget - self.heightMarge)
        self.widget.tableWidget.move(int(self.widthMarge/2), 50)

        # Affichage du bon stack
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)
        self.widget.configureBtn.clicked.connect(self.openConfigurationDialog)
        self.widget.statisticsBtn.clicked.connect(self.displayStatistics)
        self.widget.stopGameBtn.clicked.connect(lambda _ : self.stopGameWidget())
        self.widget.goBackBtn.clicked.connect(self.goBackToConfiguration)

        # Initialisation des joueurs
        self.player1 = None
        self.player2 = None
        self.plateau = None

        # Ouverture de boîte de dialogue pour la configuration du jeu
        self.configure_dialog = ConfigurationDialog.ConfigurationDialog()
        self.widget.show()

    def fillStatisticsTable(self):
        data=DataBaseHandler.StatisticsDataBaseController()
        contentToDisplay = data.display()

        self.widget.tableWidget.setRowCount(len(contentToDisplay))
        self.widget.tableWidget.setColumnCount(data.nbAttribute)

        row = 0
        for i in range(len(contentToDisplay)):
            sqlRow = contentToDisplay[i]
            for col in range(0, data.nbAttribute):
                self.widget.tableWidget.setItem(row, col, QtGui.QTableWidgetItem(str(sqlRow[col])))
            row += 1
        data.close()

    def goBackToConfiguration(self):
        """
        Goes back to the configuration widget
        :return:
        """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Configuration)

    def stopGameWidget(self):
        """
        Configures the closing of the game when the player clicks on the return button
        :return:
        """
        self.goBackToConfiguration()
        self.gameBoard.close()
        self.gameBoard.deleteLater()
        self.gameBoard = None

    def openConfigurationDialog(self):
        """ Opens several Dialogs to input the information
            for the type of the players. It mades thanks to the
            class ConfigurationDialog in the eponym module. """
        self.configure_dialog.initUI()
        self.player1 = self.configure_dialog.player1
        self.player2 = self.configure_dialog.player2
        self.play()

    def play(self):
        """
        Launchs the game
        :return:
        """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Game)
        self.gameBoard = GameBoard(self.player2, self.player1,
                               self.sizeImage, self.nbRows, self.widget)
        self.gameBoard.setParent(self.widget.boxGame)
        # Si on enlève le + 1, la taille est trop petite
        self.widget.boxGame.resize((self.nbRows + 1)*self.sizeImage,
                                   (self.nbRows + 1)*self.sizeImage)

        position  = int((self.widthWidget - self.nbRows*self.sizeImage)/2)
        self.widget.boxGame.move(position, int(self.heightMarge/2))
        self.gameBoard.show()
        QtCore.QTimer.singleShot(500, self.gameBoard.play)

    def displayStatistics(self):
        """
        Go to the Statistics widet and displays statistics
        :return:
        """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Statistics)
        self.fillStatisticsTable()





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
            self.update()
            if not self.humanTurn():
                QtCore.QTimer.singleShot(100, self.playTurn)

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

app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")
GraphicInterface(widget, 60, 8)
app.exec_()
