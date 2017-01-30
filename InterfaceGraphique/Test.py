# -*- coding: utf-8 -*-

import unittest
from hypothesis import given, settings
from boardgame_ai_py import *
import hypothesis.strategies as st

class CasDeTest(unittest.TestCase):
    def setUp(self):
        self.player1 = AlphaBetaPlayer(PawnNumberEvaluation(), 3)
        self.player2 = MinMaxPlayer(PawnNumberEvaluation(), 3)
        self.player3 = RandomPlayer()
        self.game1 = Game(8, self.player1, self.player3)
        self.game2 = Game(8, self.player2, self.player3)

    # Pas joli, le i sert à rien mais au moins ça tourne 100 fois
    @given(st.integers())
    @settings(max_examples = 100)
    def test_equal_outcome(self, _i):
        self.game1.playGameWithoutDisplay()
        self.game2.playGameWithoutDisplay()
        self.assertEqual(self.game1.gameState.board, self.game2.gameState.board)




if __name__ == '__main__':
    unittest.main()