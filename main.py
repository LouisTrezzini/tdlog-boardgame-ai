# coding: utf-8
from boardgame_ai_py import *


player1 = RandomPlayer()
player2 = RandomPlayer()
game = Game(8, player1, player2)

b = Board(8)
g = GameState(b, Color.EMPTY)

print(Game.getWinner(g) == Color.EMPTY)
print(game)

