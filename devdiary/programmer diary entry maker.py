import datetime
import os
import socket
dir = 0
counter = ""
yesorno = input("ruoyu or jason logging")
if(yesorno[0]=="r" or yesorno[0] == "R"):
	dir = "devJournal.txt"
	counter = "counter2.txt"
elif (yesorno[0]=="j" or yesorno[0] == "J"):
	dir = "devDiary.txt"
	counter = "counter.txt"
lines = []
with open(counter, 'r') as b:
    for line in b:
        lines.append(line[0:])
print("starting to make entry")
title = input("title of your marvolous art work?\n >>>")
desc = input("description of the mona lisa? (make this a breif TLDR; a summary)")
m = int(str(lines[0]))
s = open(counter, "w")
m+=1
s.write(str(m))
s.close()
h = open(dir, "a")
h.write("\n=====================\nJournal Entry #"+str(m)+"\nAt: "+str(datetime.datetime.now())+"\nTitle: "+title+"\n Description:"+desc+"\nAuthor: "+str(socket.gethostname())+"\n====================\nContents:\n")
h.close()
print("entry done")
