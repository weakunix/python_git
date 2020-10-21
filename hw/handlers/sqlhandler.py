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
    data = read(table, key)
    if valueofdupe in data:
        return True
    return False

'''
@staticmethod 
    def checkForUserAlreadyExists(username):
        data = File.getFileContents("logininfo.json")
        if username in data:
            return True
        return False
'''

if __name__ == "__main__":
    #arrayOfItems = read("kid", "*")
    #arrayOfItems = write("kid", '''"person",  "1933-1-2", "F", "B+", Null, Null''')
    #print(arrayOfItems)
    raise SystemExit("wrong file again... smh")