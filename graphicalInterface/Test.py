# -*- coding: utf-8 -*-

import unittest
from hypothesis import given, settings
from boardgame_ai_py import *
import hypothesis.strategies as st

class OutcomeTest(unittest.TestCase):
    def setUp(self):
        self.player1 = AlphaBetaPlayer(PawnNumberEvaluation(), 3, False)
        self.player2 = MinMaxPlayer(PawnNumberEvaluation(), 3, False)
        self.player3 = RandomPlayer(False)
        self.player4 = RandomPlayer(False)

    @given(st.integers())
    @settings(max_examples = 100)
    def test_equal_outcome_between_MinMax_and_AlphaBeta(self, i):
        self.game1 = Game(8, self.player1, self.player3)
        self.game2 = Game(8, self.player2, self.player4)

        # 2147483647 is the maximum integer for the seed
        RandomPlayer.seedGenerator(i % 2147483648)
        self.game1.playGameWithoutDisplay()

        RandomPlayer.seedGenerator(i % 2147483648)
        self.game2.playGameWithoutDisplay()

        self.assertEqual(self.game1.gameState.board, self.game2.gameState.board)

    @given(st.integers())
    @settings(max_examples = 10)
    def test_game_always_plays_the_same_way(self, i):
        self.game1 = Game(8, self.player1, self.player2)
        self.game2 = Game(8, self.player1, self.player2)

        RandomPlayer.seedGenerator(i % 2147483648)
        self.game1.playGame()

        RandomPlayer.seedGenerator(i % 2147483648)
        self.game2.playGameWithoutDisplay()

        self.assertEqual(self.game1.gameState.board, self.game2.gameState.board)


class EvaluationTest(unittest.TestCase):
    def setUp(self):
        self.player1 = RandomPlayer(False)
        self.player2 = RandomPlayer(False)

        self.game = Game(8, self.player1, self.player2)

        self.game.playGameWithoutDisplay()

    @given(st.integers(), st.integers(), st.integers())
    @settings(max_examples = 100)
    def test_linear_combination(self, i, j, k):
        self.coefficients = DoubleVector([i, j, k])
        self.evalFunctions = EvalFctPtrVector([PawnNumberEvaluation(), MobilityEvaluation(), PositionEvaluation()])

        self.combinationEvaluation = LinearCombinationEvaluation(self.coefficients, self.evalFunctions)

        self.pawnNumberEvaluation = PawnNumberEvaluation()
        self.mobilityEvaluation = MobilityEvaluation()
        self.positionEvaluation = PositionEvaluation()

        self.firstValue = self.combinationEvaluation.evaluate(self.game.gameState, Color.WHITE)
        self.secondValue = i * self.pawnNumberEvaluation.evaluate(self.game.gameState, Color.WHITE) + \
        j * self.mobilityEvaluation.evaluate(self.game.gameState, Color.WHITE) + \
        k * self.positionEvaluation.evaluate(self.game.gameState, Color.WHITE)

        self.assertEqual(self.firstValue, self.secondValue)






if __name__ == '__main__':
    unittest.main()