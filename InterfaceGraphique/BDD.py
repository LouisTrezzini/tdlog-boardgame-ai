import sqlite3
from boardgame_ai_py import *
import types

class dataBase:
	""" Stores the best scores and calculates the statistics. """

	def __init__(self):
		#create a data base
		self.conn = sqlite3.connect(':memory:')
		self.cur = self.conn.cursor()
		self.cur.execute("""CREATE TABLE IF NOT EXISTS scoreOthello (algo1 TEXT, eval1 TEXT, algo2 TEXT,
						eval2 TEXT, bestScore INTEGER, nbPartiesJouees INTEGER, nbVictoire INTEGER)""")
		self.conn.commit()

	def actualise(self, player1, player2, score):
		#variables with "1" correspond to the winner
		#add to the data base

		algo1 = str(type(player1))
		algo2 = str(type(player2))
		eval1 = 'None'
		eval2 = 'None'
		#TODO rajouter les conditions pour les fonctions d'évalutaion
		if isinstance(player1, HumanPlayer):
			eval1 = player1.name
		if isinstance(player2, HumanPlayer):
			eval2 = player2.name

		self.cur.execute("SELECT algo1, eval1, algo2, eval2 From scoreOthello")
		result = self.cur.fetchall()
		if (algo1,eval1,algo2,eval2) not in result:
			#FIXME Faire passer le 32 en variable
			self.cur.execute("INSERT INTO scoreOthello VALUES (?,?,?,?,?,?,?)",
							 (algo1, eval1, algo2, eval2, score, 1, int(score>32)))
			self.conn.commit()
		#OR actualise the data
		else:
			self.cur.execute("""SELECT bestScore FROM scoreOthello WHERE algo1="{}" AND eval1 = "{}"
							AND algo2  = "{}" AND eval2 = "{}" """.format(algo1, eval1, algo2, eval2))
			newScore = max(self.cur.fetchone()[0],score)
			#FIXME Faire passer le 32 en variable
			self.cur.execute("""UPDATE scoreOthello SET bestScore = {}, nbPartiesJouees = nbPartiesJouees + 1,
							nbVictoire = nbVictoire + {} WHERE algo1="{}" AND eval1 = "{}" AND algo2  = "{}"
							AND eval2 = "{}" """.format(newScore, int(score>32), algo1, eval1, algo2, eval2))
			self.conn.commit()

	def display(self):
		#Affichage
		self.cur.execute("SELECT * FROM scoreOthello")
		return self.cur.fetchall()

	def close(self):
		self.cur.close()
		self.conn.close()
    

