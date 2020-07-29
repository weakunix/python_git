#imports
import numpy as np

#vars
count = 1
is_true = False

#user def functions
##check if prime
def is_prime(num):
    for i in range(2, int(np.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

#check for odd composite number that can't be written as the sum of a prime and twice a sqaure
while True:
    is_true = False
    count += 2
    if not is_prime(count):
        for i in range(1, count + 1):
            if count > 2 * i ** 2:
                if is_prime(count - 2 * i ** 2):
                    is_true = True
                    break
        if not is_true:
            raise SystemExit(str(count))
