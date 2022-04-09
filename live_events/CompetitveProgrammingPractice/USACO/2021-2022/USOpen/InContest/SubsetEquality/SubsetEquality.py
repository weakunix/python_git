'''
SAMPLE INPUT:
aabcd
caabd
4
a
ac
abd
abcd
SAMPLE OUTPUT:
YNYN
'''

#Vars
s = input()
t = input()
Q = int(input())
Queries = [[i for i in input()] for _ in range(Q)]

#Main
if __name__ == '__main__':
    for q in Queries:
        NewS = ''
        NewT = ''
        for i in s:
            if i in q:
                NewS += i
        for i in t:
            if i in q:
                NewT += i
        if NewS == NewT:
            print('Y', end = '')
        else:
            print('N', end = '')
    print()
