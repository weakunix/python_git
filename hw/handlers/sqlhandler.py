#imports
import mysql.connector
import json
import random

def cleanUp(cursor, cnx):
    cursor.close()
    cnx.close()

def setup():
    config = json.load(open("cornfiguration.json"))
    cnx = mysql.connector.connect(**config)
    return cnx

def write(database, keys, values):
    cnx = setup()
    cursor  = cnx.cursor()
    try:
        inject = (
            "INSERT INTO %s "
            "(%s) "
            "VALUES (%s);"
        )
        cursor.execute(inject, (database, keys, values)) #injects username and password as new set in database
        cnx.commit()
        cleanUp(cnx, cursor)
        return read(database, "*")
    except Exception:
        cleanUp(cnx, cursor)
        print(Exception)
        return False

def read(database, selected):
    cnx = setup()
    cursor  = cnx.cursor()
    try:
        query = ("Select %s FROM %s")
        cursor.execute(query, (selected, database))
        cleanUp(cnx, cursor)
        return cursor #gotta do whatever with the values
    except Exception:
        cleanUp(cnx, cursor)
        print(Exception)
        return False

if __name__ == "__main__":
    raise SystemExit("wrong file again... smh")