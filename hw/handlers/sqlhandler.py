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
            ) #if there is a value to be ignored (eg, auto incriment)
        else:
            inject = (
                f"INSERT INTO {table} VALUES ({values});"
            ) #regular inject
        cursor.execute(inject) #injects username and password as new set in database
        cnx.commit() #commit the injection
        cleanUp(cnx, cursor) #closes all connections
        return read(table, "*") #returns the new table's values (if needed)
    except Exception as e:
        cleanUp(cnx, cursor)
        print(e)
        return False

def read(table, selected, condition = "", order = ""):
    cnx = setup()
    cursor  = cnx.cursor()
    try:
        query = (f"SELECT {selected} FROM {table} {condition} {order};") #conditon and order are "" on default so they won't impact anything but can be put in if needed
        cursor.execute(query) #read
        arrayOfItems = [] 
        for item in cursor:
            arrayOfItems.append(item)
        cleanUp(cnx, cursor) #close all connections
        return arrayOfItems #give back data in a array format
    except Exception as e:
        cleanUp(cnx, cursor)
        print(e)
        return False

def checkForDuplicate(table, key, valueofdupe):
    data = read(table, key, f'''WHERE {key} = "{valueofdupe}"''') #where the colomn has the duplicate value
    return True if data != [] else False #if there is already then TRUE YOU HAVE DUPE else FALSE you don't

if __name__ == "__main__":
    #arrayOfItems = read("kid", "*")
    #print(checkForDuplicate("kid", "blood", "O "))
    #print(write("kid", '''"person",  "1933-1-2", "F", "B+", Null, Null'''))
    raise SystemExit("wrong file again... smh")