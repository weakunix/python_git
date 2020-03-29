#imports
import numpy as np

#vars
mostp = 0
coprod = 0
n = 0
prime = True
eans = 0

#user def functions
def find_equation_ans(a, b, n):
    ans = n ** 2 + a * n + b
    return ans

def identify_prime(n):
    if n < 0:
        return False
    sqrtn = int(np.sqrt(n))
    for i in range(1, sqrtn + 1):
        if n % i == 0 and i != 1:
            return False
    return True

#find a and b for largest number of consecutive prime values in equation n ** 2 + a*n + b starting with n == 0
for a in range(-999, 1000):
     for b in range(-1000, 1001):
         if b % 2 == 0 or b % 3 == 0 or b % 5 == 0 or b % 7 == 0 or b % 11 == 0:
             continue
         n = -1
         prime = True
         while prime:
            n += 1
            print(a, b, n)
            prime = find_equation_ans(a, b, n)
            prime = identify_prime(prime)
         n += 1
         if n > mostp:
             mostp = n
             res = (a,b)
print('a={} b={} prod={}'.format(res[0], res[1], res[0]*res[1]))
