#Imports
import numpy as np

#Vars
Fib = [0, 1]
FinalSum = 0
PowersOf10 = [10]

#Set up Fibonacci array
for i in range(2, 91):
    Fib.append(Fib[i - 2] + Fib[i - 1])

#Precomputed powers of 10
for i in range(int(np.log2(Fib[-1]))):
    PowersOf10.append(PowersOf10[-1] ** 2 % 1000000007)

#User def functions
##Power mod
def powermod(n, PowerList):
    k = 0
    r = 1
    while n > 0:
        if n % 2:
            r *= PowerList[k]
            r %= 1000000007
        n >>= 1
        k += 1
    return r

##Big s function
def s(n):
    #Num = (n % 9 + 1) * power10mod(n // 9) - 1
    k = n // 9
    r = n % 9
    Num = 5 * (powermod(k, PowersOf10) - 1) - 9 * k + powermod(k, PowersOf10) * (r + 1) * (r + 2) / 2 - r - 1
    return Num % 1000000007



#Calculate final sum
if __name__ == '__main__':
    for _ in range(2):
        Fib.pop(0)
    for i in Fib:
        FinalSum += s(i)
    print(FinalSum % 1000000007)
