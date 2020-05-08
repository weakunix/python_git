#imports
import numpy as np

#vars
count = 0
alln = []
num = 9

#user def functions
#check if prime
def is_prime(x):
    for i in range(2, int(np.sqrt(x) + 1)):
        if x % i == 0:
            return False
    return True

#left truncation
def left_to_right(x):
    if not is_prime(x):
        return False
    while len(str(x)) != 1:
        x = int(str(x)[1:])
        if not is_prime(x):
            return False
    if x == 1:
        return False
    return True

#right truncation
def right_to_left(x):
    if not is_prime(x):
        return False
    for i in range(len(str(x)) - 1):
        x = int(str(x)[:-1])
        if not is_prime(x):
            return False
    if x == 1:
        return False
    return True

#trying all numbers to find 11 truncatable primes
while count != 11:
    num += 1
    if left_to_right(num) and right_to_left(num):
        count += 1
        alln.append(num)
print(sum(alln), alln)
