#imports
import numpy as np

#vars
count = -1

#lists
n = []
d = []
a = []

#user def functions
def divisor_sum(n):
    d = []
    sqrtn = int(np.sqrt(n))
    for i in range(1, sqrtn + 1):
        if n % i == 0:
            d.append(i)
    dsum = sum(d)
    for i in d:
        dsum += n / i
    dsum -= n
    if sqrtn ** 2 == n:
        dsum -= sqrtn
    return dsum
    

#find amicable number pairs
for i in range(1, 10000):
    ds = divisor_sum(i)
    ami = False
    count = -1
    for k in d:
        count += 1
        if i == k and ds == n[count]:
            ami = True
            a.append(d.pop(count))
            a.append(n.pop(count))
            break
    if ami == False:
        n.append(i)
        d.append(ds)
print(sum(a))
