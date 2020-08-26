#imports
import numpy as np

#vars
count = 10 ** 7

#user def functions
#check if pandigital
def pand_check(num):
    num = list(str(num))
    for i in range(1, len(num) + 1):
        if str(i) not in num:
            return False
    return True

#check if prime
def prime_check(num):
    for i in range(2, int(np.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

#searching for largest pandigital prime from 10 ^ 7 (as 8 and 9 digit pandigital numbers won't be prime (divisible by 3))
while 1:
    count -= 1
    if pand_check(count) and prime_check(count):
        print(count)
        break
