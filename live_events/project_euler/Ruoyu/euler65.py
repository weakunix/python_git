'''
Observations:
Must keep fraction since we need numerator
a + b/c = (ac + b)/c

Possibilities:
Generate 100 elements of e sequence (2, 1, 2, 1, 1, 4, 1, 1, 6...)
100 elements because each element leads to one more convergent
Go backward and add fractions
'''

#Vars
ESeq = [] #e sequence
DigitSum = 0 #100th convergent digit sum

#User def functions
def GenESeq() -> list:
    ESeq = [2, 1, 2]
    Count = 2
    while len(ESeq) <= 97:
        Count += 2
        ESeq += [1, 1, Count]
    for i in range(len(ESeq), 100):
        ESeq.append(1)
    return ESeq

def Gcd(a, b) -> int:
    while a != 0 and b != 0:
        a %= b
        if a == 0:
            return b
        b %= a
        if b == 0:
            return a

if __name__ == '__main__':
    ESeq = GenESeq()
    n = 1
    d = ESeq.pop()
    while len(ESeq) > 0:
        i = ESeq.pop()
        n = i * d + n
        g = Gcd(n, d)
        #import pdb;pdb.set_trace()
        n //= g
        d //= g
        temp = n
        n = d
        d = temp
    print(d) #Numerator and denominator will be flipped one extra time thus the answer we are looking for is the denominator
    for i in str(d):
        DigitSum += int(i)
    print(DigitSum)
