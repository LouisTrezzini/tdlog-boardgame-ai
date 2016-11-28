# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, uic
from boardgame_ai_py import *

app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")

widget.RulesButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_2))
widget.RulesButtonTab3.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_2))
widget.RulesButtonTab4.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_2))
widget.RulesButtonTab5.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_2))

widget.ComeBackButtonTab3.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab))
widget.ComeBackButtonTab4.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab))
widget.ComeBackButtonTab5.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab))
widget.playButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab))

widget.TwoPlayersButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_3))
widget.OnePlayerButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_4))
widget.ZeroPlayerButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_5))

widget.show()

app.exec_()