#imports
import numpy as np

#vars
alln = []
alld = []
n1 = 0
n2 = True

for n in range(10, 100):
    for d in range(10, 100):
        n2 = True
        n = str(n)
        d = str(d)
        if '0' in n:
            n2 = False
        if '0' in d:
            n2 = False
        n = int(n)
        d = int(d)
        if n / d < 1 and n2 == True:
            i = n
            k = d
            n1 = i / k
            i = str(i)
            k = str(k)
            i = [i[0], i[1]]
            k = [k[0], k[1]]
            if i[0] == k[0]:
                i.pop(0)
                k.pop(0)
            elif i[0] == k[1]:
                i.pop(0)
                k.pop(1)
            elif i[1] == k[0]:
                i.pop(1)
                k.pop(0)
            elif i[1] == k[1]:
                i.pop(1)
                k.pop(1)
            else:
                n2 = False
            if n2 != False and int(i[0]) != 0 and int(k[0]) != 0:
                n2 = int(i[0]) / int(k[0])
            if n1 == n2:
                alln.append(n)
                alld.append(d)
alln = np.prod(alln)
alld = np.prod(alld)
n1 = alln
n2 = alld
while n1 != 0 and n2 != 0:
    n1 %= n2
    if n1 == 0:
        alln = n2
        break
    n2 %= n1
    if n2 == 0:
        alln = n1 
print(alld / alln)
