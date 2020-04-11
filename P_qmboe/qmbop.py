#imports
import random
import datetime

#user def functions

#qmbo one
def qmboone():
    c = ''
    p = ''
    cap = 0
    l = {	1: ['C', 'c'],
            2: ['O', 'o'],
            3: ['W', 'w'],
            4: ['L', 'l'],
            5: ['A', 'a'],
            6: ['N', 'n'],
            7: ['D', 'd'] }
    n = random.randint(2, 5)
    for i in range(1, 8):
        i = str(i)
        cap = random.randint(1, 2)
        p += i
        if cap == 2:
            p += i
            i = int(i)
            c += (l[i][0])
        else:
            i = int(i)
            c += (l[i][1])
    p = [c, (int(p) * n) ** n, n]
    print(p[0])#remove this later
    c = input('{}!{}:\n'.format(p[2], p[1]))
    if c == p[0]:
        return True
    return False

#qmbo two
def qmbotwo():
    alpha = ' abcdefghijklmnopqrstuvwxyz'
    p = random.randint(1, 23)
    num = int((26 - p) / 3)
    p = [p, p + num, p + 2 * num, p + 3 * num]
    num = input('{}\n'.format(p[:3]))
    if num == alpha[p[3]]:
        return True
    return False

#qmbo three
def qmbothree():
    t = str(datetime.datetime.today())
    p = [int(t[:4]), int(t[5:7]), int(t[8:10]),int(t[11:13]), int(t[14:16]), int(t[17:19]), int(t[20:])]
    p = sum(p)
    print(p)
    c = int(input('Loging in at time {}?\n'.format(t)))
    if c == p:
        return True
    else:
        return False
#s = qmbothree() ruoyu this was what was making it print login at time in the beginning. IDK if u want to keep or remove
#print(s)

