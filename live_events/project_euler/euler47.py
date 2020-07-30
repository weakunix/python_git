#imports
import numpy as np

#vars
num = 0 #(def)the first of the four consecutive integers
nums = [] #(def)four consecutive integers to test
skip_to = 1 #if one number doesn't work then skip past that number

#user def functions
##test if there are 4 and only 4 prime factors
def is_four_factors(num):
    onum = num
    factors = []
    prime = True
    for i in range(2, num + 1):
        prime = True
        if num % i == 0:
            for k in factors:
                if i % k == 0:
                    prime = False
                    break
            if prime:
                factors.append(i)
                if len(factors) > 4:
                    return [False, onum]
                while num % i == 0:
                    num /= i
    if len(factors) < 4:
        return [False, onum]
    else:
        #print(factors)
        return [True, onum]

#testing for four consecutive integers with distinct factors each
'''
SUPER BRUTE FORCE METHOD (SLOW)
while True:
    num += 1
    print(num)
    nums = []
    for i in range(4):
        nums.append(num + i)
    for i in nums:
        skip_to = is_four_factors(i)
        if not skip_to[0]:
            break
    if skip_to[0]:
        print(skip_to[1] - 3)
        break
'''

while True:
    num = skip_to
    print(num) #CAN DELETE LATER
    skip_to = None
    nums = []
    for i in range(4):
        nums.append(num + i)
    for i in nums:
        num = is_four_factors(i)
        if not num[0]:
            skip_to = num[1] + 1
    if skip_to == None:
        num = num[1]
        break
print('\n{}'.format(num - 3))
