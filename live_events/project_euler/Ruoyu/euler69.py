#Vars
MaxVal = 0 #n / totient(n)
CurrentVal = 0
MaxN = 0
Primes = []

#User def functions
##Get prijme factors
def GetPrimeFactors(n):
    global Primes
    pfs = [n]
    for i in Primes:
        if not n % i:
            pfs.append(i)
    if len(pfs) == 1:
        Primes.append(n)
    return pfs

##Totient function
def Totient(n):
    Notmp = set() #Not mutually prime numbers
    pfs = GetPrimeFactors(n)
    for i in pfs:
        for k in range(1, n // i + 1):
            Notmp.add(i * k)
    return n - len(Notmp)

if __name__ == '__main__':
    for n in range(2, 10 ** 6 + 1):
        if not n % 1000:
            print(n)
        CurrentVal = n / Totient(n)
        if CurrentVal > MaxVal:
            MaxVal = CurrentVal
            MaxN = n
    print(MaxN)
