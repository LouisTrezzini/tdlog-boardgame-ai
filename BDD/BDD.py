#creer une base de données
import sqlite3
conn = sqlite3.connect(':memory:')
cur = conn.cursor()
cur.execute("CREATE TABLE scoreOthello (pseudo TEXT, typeAdversaire TEXT, meilleurScore INTEGER, nbPartiesJouees INTEGER, nbVictoire INTEGER) IF NOT EXISTS scoreOthello") 
conn.commit()

#Completer la bdd à la fin du jeu
#victoire ou défaite du player 1 ?
if (game.GameState.Board.getBlackStones()>=game.GameState.Board.getWhitetones()):
	victoire=1
else:
	victoire=0
#ajouter à la base de données
if (player1.name,player2.type not in "SELECT pseudo,typeAdversaire From scoreOthello"):
	cur.execute("INSERT INTO scoreOthello(pseudo,typeAdversaire, meilleurScore, nbPartiesJouees, pourcentageVictoire) VALUES(player1.name,player2.type,game.GameState.Board.getBlackStones(),1,victoire)")
	conn.commit()
#OU actualiser la base de données
else: 
	cur.execute("SELECT meilleurScore FROM scoreOthello WHERE pseudo=player1.name")
	score1 = max(cur.fetchone(),game.GameState.Board.getBlackStones())
	cur.execute("UPDATE scoreOthello SET meilleurScore=score1, nbPartiesJouees=nbPartiesJouees+1,nbVictoire=nbVictoire+victoire WHERE pseudo=player1.name, typeAdversaire=player2.type")
	conn.commit()
#Idem player2
if (player2.name,player1.type not in "SELECT pseudo,typeAdversaire From scoreOthello"):
	cur.execute("INSERT INTO scoreOthello(pseudo,typeAdversaire, meilleurScore, nbPartiesJouees, pourcentageVictoire) VALUES(player2.name,player1.type,game.GameState.Board.getWhiteStones(),1,abs(1-victoire))")
	conn.commit()
else: 
	cur.execute("SELECT meilleurScore FROM scoreOthello WHERE pseudo=player2.name")
	score2 = max(cur.fetchone(),game.GameState.Board.getWhiteStones())
	cur.execute("UPDATE scoreOthello SET meilleurScore=score2, nbPartiesJouees=nbPartiesJouees+1,nbVictoire=nbVictoire+victoire WHERE pseudo=player2.name, typeAdversaire=player1.type")
	conn.commit()

#Affichage
cur.execute("SELECT * FROM scoreOthello")
cur.fetchall()

#fermer la base de donnée
cur.close() 
conn.close()
    

