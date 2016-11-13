# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, uic

app = QtGui.QApplication(sys.argv)
widget = uic.loadUi("mainwindow.ui")
widget.show()

app.exec_()