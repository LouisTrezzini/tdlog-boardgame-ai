from PyQt4 import QtCore

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
