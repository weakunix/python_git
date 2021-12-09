#Imports
import numpy as np

#Vars
ToTestNums = []
ToTestDigits = []
Primes = []
CurrentPow = 0

#User def functions
def IsPrime(n):
    if n <= 1:
        return False
    MaxTest = int(np.sqrt(n))
    for k in Primes:
        if k > MaxTest:
            return True
        if n % k == 0:
            return False
    return True

def IsPossibleNum(n):
    strn = str(n)
    for digit in range(10):
        Occurence = strn.count(str(digit))
        if Occurence > 0 and Occurence % 3 == 0:
            ToTestNums.append(n)
            ToTestDigits.append(digit)

#Test
while True:
    CurrentPow += 1
    ToTestNums = []
    ToTestDigits = []
    for i in range(10 ** (CurrentPow - 1), 10 ** CurrentPow + 1):
        if IsPrime(i):
            Primes.append(i)
            IsPossibleNum(i)
            print(i)
    for i in range(len(ToTestNums)):
        TestNum = ToTestNums[i]
        TestDigit = ToTestDigits[i]
        Count = 0
        for k in range(10):
            if int(str(TestNum).replace(str(TestDigit), str(k))) in Primes:
                Count += 1
        if Count == 8:
            print(TestNum)
            break
