#imports
from __future__ import print_function #featuring Drake
import mysql.connector
import json
import random
import string
config = json.load(open("cornfiguration.json"))

#actual code vvvvv
cnx = mysql.connector.connect(**config)
cursor  = cnx.cursor()

query = ("SELECT * from test")

inject = ("INSERT INTO test "
              "(name, password) "
              "VALUES (%s, %s);"
)

for i in range(random.randint(0,20)):
    cursor.execute(inject, (
        "".join([random.choice(string.ascii_letters) for i in range(random.randint(1, 10))])
        , "".join([random.choice(string.ascii_letters) for i in range(random.randint(1, 10))])
        )
    )
    cnx.commit()

cursor.execute(query)

for i in cursor:
    print(i)

#close
cursor.close()
cnx.close()