import sqlite3

class dataBase:
	""" Stores the best scores and calculates the statistics. """

	def __init__(self):
		#create a data base
		self.conn = sqlite3.connect(':memory:')
		self.cur = conn.cursor()
		self.cur.execute("CREATE TABLE IF NOT EXISTS scoreOthello (pseudo TEXT, typeAdversaire TEXT, meilleurScore INTEGER, nbPartiesJouees INTEGER, nbVictoire INTEGER)") 
		self.conn.commit()

	def actualise(self,name1,type1,score1,name2,type2,score2):
		#variables with "1" correspond to the winner
		#add to the data base
		if (name1,type2 not in "SELECT pseudo,typeAdversaire From scoreOthello"):
			self.cur.execute("INSERT INTO scoreOthello(pseudo,typeAdversaire, meilleurScore, nbPartiesJouees, nbVictoire) VALUES (name1,type2,score1,1,1)")
			self.conn.commit()
		#OR actualise the data
		else: 
			self.cur.execute("SELECT meilleurScore FROM scoreOthello WHERE pseudo=name1")
			score = max(cur.fetchone(),score1)
			self.cur.execute("UPDATE scoreOthello SET meilleurScore=score, nbPartiesJouees=nbPartiesJouees+1,nbVictoire=nbVictoire+1 WHERE pseudo=name1, typeAdversaire=type2")
			self.conn.commit()
		#Ditto for player2
		if (name2,type1 not in "SELECT pseudo,typeAdversaire From scoreOthello"):
			self.cur.execute("INSERT INTO scoreOthello(pseudo,typeAdversaire, meilleurScore, nbPartiesJouees, nbVictoire) VALUES(name2,type1,score2,1,0)")
			self.conn.commit()
		else:
			self.cur.execute("SELECT meilleurScore FROM scoreOthello WHERE pseudo=name2")
			score = max(cur.fetchone(),score2)
			self.cur.execute("UPDATE scoreOthello SET meilleurScore=score, nbPartiesJouees=nbPartiesJouees+1 WHERE pseudo=name2, typeAdversaire=type1")
			self.conn.commit()

	def display(self):
		#Affichage
		self.cur.execute("SELECT * FROM scoreOthello")
		self.cur.fetchall()

	def close(self):
		self.cur.close()
		self.conn.close()
    

