# -*- coding: utf-8 -*-

import sys
import GraphicalInterface
from PyQt4 import QtGui, QtCore, uic
from boardgame_ai_py import *


app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("MainWindow.ui")
GraphicalInterface.GraphicalInterface(widget, 60, 8)
app.exec_()
