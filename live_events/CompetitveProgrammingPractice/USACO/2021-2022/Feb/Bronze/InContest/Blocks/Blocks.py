'''
Sample Cases:
In:
6
MOOOOO
OOOOOO
ABCDEF
UVWXYZ
COW
MOO
ZOO
MOVE
CODE
FARM

Out:
YES
NO
YES
YES
NO
NO

CORRECT PROGRAM!
20/20
'''

#User def functions
def WordDict(s) -> dict:
    temp = {}
    for i in range(4):
        try:
            i = s[i]
            try:
                temp[i] += 1
            except:
                temp[i] = 1
        except:
            try:
                temp[None] += 1
            except:
                temp[None] = 1
    return temp

#Main
N = int(input())
Dice = []
Words = []
for _ in range(4):
    Dice.append(list(set(input())))
for _ in range(N):
    Words.append(WordDict(input()))

Spellable = ['NO' for _ in range(N)]

for a in range(-1, len(Dice[0])):
    if a == -1:
        a = None
    else:
        a = Dice[0][a]
    for b in range(-1, len(Dice[1])):
        if b == -1:
            b = None
        else:
            b = Dice[1][b]
        for c in range(-1, len(Dice[2])):
            if c == -1:
                c = None
            else:
                c = Dice[2][c]
            for d in range(-1, len(Dice[3])):
                if d == -1:
                    d = None
                else:
                    d = Dice[3][d]
                temp = {}
                for i in [a, b, c, d]:
                    try:
                        temp[i] += 1
                    except:
                        temp[i] = 1
                for i, word in enumerate(Words):
                    if temp == word:
                        Spellable[i] = 'YES'
for i in Spellable:
    print(i)
