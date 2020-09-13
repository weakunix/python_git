#imports
import numpy as np

#vars
work = set() #maybe working numbers
digits = '' #digits of a number
permutations = [] #permutations of a number

#user def functions
##test for prime
def is_prime(x):
    for i in range(2, int(np.sqrt(x)) + 1):
        if x % i == 0:
            return False
    return True

##test for permutation
def is_perm(x, y):
    #import pdb;pdb.set_trace()
    nums = []
    y = str(y)
    for i in str(x):
        nums.append(i)
    for i in y:
        if i not in nums:
            return False
        for k in range(len(nums)):
            if nums[k] == i:
                nums.pop(k)
                break
    return True

if __name__ == '__main__':
    #testing all 4 digit numbers to see if they are maybe prime
    for i in range(1000, 10000):
       if is_prime(i):
           work.add(i)

    #test for permutations
    for i in work:
        permutations = []
        digits = str(i)
        for k in work:
            if is_perm(k, digits):
                permutations.append(k)
        if len(permutations) >= 3 and 1487 not in permutations:
            for a in permutations:
                for b in permutations:
                    if b > a:
                        if 2 * b - a in permutations:
                            digits = str(a) + str(b) + str(2 * b - a)
                            raise SystemExit(f'{digits}')
