#imports
import numpy as np

#vars
num = ''
prod = []

#getting 1000000 numbers stringed together
for i in range(1000000):
    num += str(i)

#finding all digits needed
prod = np.prod([int(num[1]), int(num[10]), int(num[100]), int(num[1000]), int(num[10000]), int(num[100000]), int(num[1000000])])
print(prod)
