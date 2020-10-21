#imports
import mysql.connector
import json
import random
import datetime

def cleanUp(cursor, cnx):
    cursor.close()
    cnx.close()

def setup():
    config = json.load(open("cornfiguration.json"))
    cnx = mysql.connector.connect(**config)
    return cnx

def write(table, values, keys = ""):
    cnx = setup()
    cursor  = cnx.cursor()
    try:
        if keys != "":
            inject = (
                f"INSERT INTO {table} ({keys}) VALUES ({values});"
            )
        else:
            inject = (
                f"INSERT INTO {table} VALUES ({values});"
            )
        cursor.execute(inject) #injects username and password as new set in database
        cnx.commit()
        cleanUp(cnx, cursor)
        return read(table, "*")
    except Exception as e:
        cleanUp(cnx, cursor)
        print(e)
        return False

def read(table, selected, condition = "", order = ""):
    cnx = setup()
    cursor  = cnx.cursor()
    try:
        query = (f"SELECT {selected} FROM {table} {condition} {order};")
        cursor.execute(query)
        arrayOfItems = []
        for item in cursor:
            arrayOfItems.append(item)
        cleanUp(cnx, cursor)
        return arrayOfItems
    except Exception as e:
        cleanUp(cnx, cursor)
        print(e)
        return False

def checkForDuplicate(table, key, valueofdupe):
    data = read(table, key, f'''WHERE {key} = "{valueofdupe}"''')
    return True if data != [] else False

if __name__ == "__main__":
    #arrayOfItems = read("kid", "*")
    #print(checkForDuplicate("kid", "blood", "O "))
    #print(write("kid", '''"person",  "1933-1-2", "F", "B+", Null, Null'''))
    raise SystemExit("wrong file again... smh")