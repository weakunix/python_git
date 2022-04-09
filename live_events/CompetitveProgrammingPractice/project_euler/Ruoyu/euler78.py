'''
Observations:
(a) Use Pentagonal Number Theorem to generate p(n)

Approach:
Store a dictionary of pentagonal numbers and p(n) to generate succeeded p(n)
'''

#Vars
Pentagonals = {} #Dict of pentagonal numbers
PrevP = {0: 1, 1: 1} #Dict of previous p(n)
n = 1 #n

#User def functions
def GetPentagonal(n) -> int:
    try:
        return Pentagonals[n]
    except:
        temp = n * (3 * n - 1) // 2
        Pentagonals[n] = temp
        return temp

def p(n) -> int:
    i = 0
    count = 0
    while True:
        i -= 1
        for k in range(2):
            i *= -1
            temp = n - GetPentagonal(i)
            if temp < 0:
                count %= 10 ** 6
                PrevP[n] = count
                return count
            temp = PrevP[temp]
            if i % 2 == 0:
                temp *= -1
            count += temp

#Main
if __name__ == '__main__':
    while True:
        n += 1
        temp = p(n)
        if n % 10000 == 0:
            print(n, temp)
        if temp == 0:
            print(n)
            break
