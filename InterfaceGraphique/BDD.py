import sqlite3
from boardgame_ai_py import *
import types


class DataBase:
    """ Stores the best scores and calculates the statistics. """

    def __init__(self):
        # créer la base de données
        self.nbAttribute=7
        self.conn = sqlite3.connect('BDD.db')
        self.cur = self.conn.cursor()
        self.cur.execute("""CREATE TABLE IF NOT EXISTS scoreOthello (type1 TEXT, name1 TEXT, type2 TEXT,
						name2 TEXT, bestScore INTEGER, numberOfPlayedGame INTEGER, numberOfVictory INTEGER)""")
        self.conn.commit()

    def actualise(self, player1, player2, score, nbRows):
        # player1 est le vainqueur de la partie

        # Ajouter ou actualiser la base de données
        # On ne sélectionne qu'une partie de la chaîne de caractère pour se débarasser de ceux inutiles
        type1 = str(type(player1))[24:-2]
        type2 = str(type(player2))[24:-2]
        name1 = 'None'
        name2 = 'None'
        # TODO rajouter les conditions pour les fonctions d'évalutaion
        if isinstance(player1, HumanPlayer):
            name1 = player1.name
        if isinstance(player2, HumanPlayer):
            name2 = player2.name

        self.cur.execute("SELECT type1, name1, type2, name2 From scoreOthello")
        result = self.cur.fetchall()
        if (type1, name1, type2, name2) not in result:
            self.cur.execute("INSERT INTO scoreOthello VALUES (?,?,?,?,?,?,?)",
                             (type1, name1, type2, name2, score, 1, int(score > nbRows**2/2)))
            self.conn.commit()
        else:
            self.cur.execute("""SELECT bestScore FROM scoreOthello WHERE type1="{}" AND name1 = "{}"
							AND type2  = "{}" AND name2 = "{}" """.format(type1, name1, type2, name2))
            newScore = max(self.cur.fetchone()[0], score)
            self.cur.execute("""UPDATE scoreOthello SET bestScore = {}, numberOfPlayedGame = numberOfPlayedGame + 1,
							numberOfVictory = numberOfVictory + {} WHERE type1="{}" AND name1 = "{}" AND type2  = "{}"
							AND name2 = "{}" """.format(newScore, int(score > nbRows**2/2), type1, name1, type2, name2))
            self.conn.commit()

    def display(self):
        self.cur.execute("SELECT * FROM scoreOthello")
        return self.cur.fetchall()

    def close(self):
        self.cur.close()
        self.conn.close()

class accessControled:
    """ Stores the password linked to each registred user. """

    def __init__(self):
        # créer la base de données
        self.conn = sqlite3.connect('Passwords.db')
        self.cur = self.conn.cursor()
        self.cur.execute("""CREATE TABLE IF NOT EXISTS password (name TEXT, password TEXT)""")
        self.conn.commit()

    def isNewPlayer(self, pseudo, password, data):
        # tester si le pseudo est entré pour la première fois
        self.cur.execute("SELECT name From password")
        result = self.cur.fetchall()
        if ((pseudo,) not in result):
            return True    
        else:
            return False

    def checkAccess(self, pseudo, password,data):
        #ajouter les nouveaux joueurs
        if (self.isNewPlayer(pseudo,password,data)):
            self.cur.execute("INSERT INTO password VALUES (?,?)",(pseudo,password))
            self.conn.commit()
        else:
        # vérifier que le mot de passe et le pseudo correspondent
            self.cur.execute("SELECT * FROM password")
            result = self.cur.fetchall()
            if ((pseudo, password) not in result):
                return False
        return True  

    def close(self):
        self.cur.close()
        self.conn.close()

        

