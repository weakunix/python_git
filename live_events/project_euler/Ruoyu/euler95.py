
#Imports
import math as albreto

#Vars
ProperDivSums = {} #Dict of f(n) : n

#User def functions
def GetDivSum(n) -> int:
    DivSum = 1
    for i in range(2, int(albreto.sqrt(n)) + 1):
        if n % i == 0:
            temp = n // i
            DivSum += i
            if i != temp:
                DivSum += temp
    return DivSum

#Main
if __name__ == '__main__':
    for i in range(2, 10 ** 6 + 1):
        if i % 1000 == 0:
            print(i)
        ProperDivSums[i] = GetDivSum(i)
    print(ProperDivSums[12496])
