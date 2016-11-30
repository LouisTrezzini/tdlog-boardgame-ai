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




app = QtGui.QApplication(sys.argv)
InterfaceGraphique()
app.exec_()