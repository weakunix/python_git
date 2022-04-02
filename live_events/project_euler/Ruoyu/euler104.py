'''
Observations:
(a) We just have to store f(n) and f(n - 1) in a list to calculate f(n)

Approach:
BFI and calculate each succeeding f(n) using Observation (a)
Test if the first 9 digits are pandigital by converting f(n) to a string and taking the first 9 digits
Test if the last 9 digits are pandigital by using mod 10 ^ 9
The pandigital test function can just be a loop where we add each digit into a set and see if the set contains all digits 1 to 9
'''

#Vars
Fib = [1, 1] #Fibonnaci numbers n and n - 1
n = 2 #n

#User def functions
def IsPandigital(n) -> bool:
    Digits = set()
    for i in str(n):
        Digits.add(i)
    return len(Digits) == 9 and '0' not in Digits

#Main
if __name__ == '__main__':
    while True:
        n += 1
        if n % 1000 == 0:
            print(n)
        Fib.append(Fib.pop(0) + Fib[0])
        if IsPandigital(Fib[1] % 10 ** 9) and IsPandigital(str(Fib[1])[:9]):
            print(n)
            break
