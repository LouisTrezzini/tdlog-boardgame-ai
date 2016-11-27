# coding: utf-8
from boardgame_ai_py import *


player1 = RandomPlayer()
player2 = RandomPlayer()
game = Game(8, player1, player2)


while (Game.getWinner(game.GameState) == Color.EMPTY):
    pickedMove = game.pickMove(game.GameState)
    game.playMove(pickedMove)
    print(game)

