#imports
import numpy as np

#vars
prime = set()
nonp = set()

#user def functions
#test for prime
def is_prime(x):
    for i in range(2, int(np.sqrt(x) + 1)):
        if x % i == 0:
            return False
    return True

#trying each number
for i in range(2, 1000000): #change to 1 million later
    p = is_prime(i)
    print(i)
    if p:
        prime.add(i)
    else:
        nonp.add(i)
for i in nonp:
    print(i)
    num = i
    for k in range(len(str(i)) - 1):
        num = int(str(num)[1:] + str(num)[0])
        if num in prime and len(str(num)) == len(str(i)):
            prime.remove(num)
print(len(prime), '\n', prime)
