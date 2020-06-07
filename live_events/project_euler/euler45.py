#imports
import numpy as np

#vars
count = 0
num = 40755

#user def functions
##test for pentagonal
def is_pentagonal(num):
    count = 1
    while count * (3 * count - 1) / 2 < num:
        count += 1
    if count * (3 * count - 1) / 2 == num:
        return True
    return False

##test for hexagonal
def is_hexagonal(num):
    count = 1
    while count * (2 * count - 1) < num:
        count += 1
    if count * (2 * count - 1) == num:
        return True
    return False

#find what n would be for n * (n + 1) / 2 = 40755
num *= 2
count = int(np.sqrt(num))

#testing all triangle numbers until it is pentagonal and hexagonal
while 1:
    count += 1
    num = count * (count + 1) / 2
    print(count, num, is_pentagonal(num), is_hexagonal(num))
    if is_pentagonal(num) and is_hexagonal(num):
        break
print(num)
