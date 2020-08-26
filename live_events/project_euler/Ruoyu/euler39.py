#imports
import numpy as np

#vars
maxn = 0
maxcount = 0
count = 0

#trying for perimeter of right triangle with max solutions
for i in range(1, 1001):
    count = 0
    for a in range(1, int(i / (2 * np.sqrt(2))) + 1):
        for b in range(a + 1, int((i - a) / 2) + 1):
            c = i - a - b
            print(i, a, b, c, maxn, maxcount)
            if a ** 2 + b ** 2 == c ** 2:
                count += 1
    if count > maxcount:
        maxn = i
        maxcount = count
print(maxn, maxcount)
