# -*- coding: utf-8 -*-

import GameBoard
import ConfigurationDialog
import DataBaseHandler
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *

class GraphicalInterface:

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

        #Personnalisation timer:
        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Foreground,QtCore.Qt.red)
        self.widget.timer.setPalette(palette)
        f = QtGui.QFont( "Helvetica", 15)
        f.setBold(True)
        self.widget.timer.setFont(f)

        # Initialisation des joueurs
        self.timeLimit = None
        self.player1 = None
        self.player2 = None
        self.plateau = None

        # Ouverture de boîte de dialogue pour la configuration du jeu
        self.configure_dialog = ConfigurationDialog.ConfigurationDialog()
        self.widget.show()

    def fillStatisticsTable(self):
        data = DataBaseHandler.StatisticsDataBaseController()
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
        self.timeLimit = self.configure_dialog.timeLimit
        self.play()

    def play(self):
        """
        Launchs the game
        :return:
        """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Game)
        self.gameBoard = GameBoard.GameBoard(self.player2, self.player1,
                               self.sizeImage, self.nbRows, self.widget)
        self.gameBoard.setParent(self.widget.boxGame)
        # Si on enlève le + 1, la taille est trop petite
        self.widget.boxGame.resize((self.nbRows + 1)*self.sizeImage,
                                   (self.nbRows + 1)*self.sizeImage)

        position  = int((self.widthWidget - self.nbRows*self.sizeImage)/2)
        self.widget.boxGame.move(position, int(self.heightMarge/2))
        self.gameBoard.show()
        QtCore.QTimer.singleShot(500, self.gameBoard.playTurn)

    def displayStatistics(self):
        """
        Go to the Statistics widet and displays statistics
        :return:
        """
        self.widget.stackedWidget.setCurrentWidget(self.widget.Statistics)
        self.fillStatisticsTable()
