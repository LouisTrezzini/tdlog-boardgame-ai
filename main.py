# coding: utf-8
from boardgame_ai_py import *

board = Board(8)
player = RandomPlayer()
g = Game(6, player, player)
m = Move(3,4)
print(m.x)
print(m.y)

print(board)

