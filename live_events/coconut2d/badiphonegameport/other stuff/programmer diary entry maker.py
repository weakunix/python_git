import datetime
import os
import socket
lines = []
with open('counter.txt', 'r') as b:
    for line in b:
        lines.append(line[:-1])
print(lines)
print("starting to make entry")
title = input("title of your marvolous art work?\n >>>")
desc = input("description of the mona lisa? (make this a breif TLDR; a summary)")
m = int(lines[0])
m+=1
s = open("counter.txt", "w")
s.write(str(m))
s.close()
h = open("devDiary.txt", "a")
h.write("\n=====================\nJournal Entry #"+str(m)+"\nAt: "+str(datetime.datetime.now())+"\nTitle: "+title+"\n Description:"+desc+"\nAuthor: "+str(socket.gethostname())+"\n====================\nContents:\n")
h.close()
print("entry done")
