#imports
import numpy as np

#vars
count = 0
alln = []

#user def functions
#shift 
def shift_num(x):
    x = str(x)
    x = x[1:] + x[0] 
    return int(x)

#test for prime
def is_prime(x):
    for i in range(2, int(np.sqrt(x))):
        if x % i == 0:
            return False
    return True

#trying each number
for i in range(2, 1000000): #change to 1 million later
    num = 0
    i = str(i)
    if '2' in i or '4' in i or '6' in i or '8' in i or '0' in i:
        i = int(i)
        if i != 2:
            i = False
    elif '5' in i and i != '5':
        i = False
    else:
        i = int(i)
        if i % 3 == 0 and i != 3:
            i = False
    if i:
        for k in range(len(str(i)) - 1):
            k = is_prime(i)
            if not k:
                i = False
                break
            i = shift_num(i)
        if i:
            alln.append(i)
            count += 1
print(count, '\n', alln)
