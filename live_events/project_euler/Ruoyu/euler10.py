#import
import numpy as np

#vars
s=2

#lists
prime=[2]

#main
for i in range(3, 2000000):
    p=True
    cap = np.sqrt(i)
    for m in prime:
        if m>cap:
            break
        if i%m==0:
            p=False
            break
    if p:
        s+=i
        prime.append(i)

print("Your sum is {}".format(s))
