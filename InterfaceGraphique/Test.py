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
        self.player4 = RandomPlayer()

    @given(st.integers())
    @settings(max_examples = 10)
    def test_equal_outcome(self, i):
        self.game1 = Game(8, self.player1, self.player3)
        self.game2 = Game(8, self.player2, self.player4)

        # 2147483647 is the maximum integer for the seed
        RandomPlayer.seedGenerator(i % 2147483648)
        self.game1.playGameWithoutDisplay()

        RandomPlayer.seedGenerator(i % 2147483648)
        self.game2.playGameWithoutDisplay()

        self.assertEqual(self.game1.gameState.board, self.game2.gameState.board)




if __name__ == '__main__':
    unittest.main()