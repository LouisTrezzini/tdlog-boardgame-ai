# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, uic

app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")

widget.RulesButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_2))
widget.TwoPlayersButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_3))
widget.OnePlayerButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_4))
widget.ZeroPlayerButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab_5))
widget.playButton.clicked.connect(lambda _ : widget.tabWidget.setCurrentWidget(widget.tab))
widget.show()

app.exec_()