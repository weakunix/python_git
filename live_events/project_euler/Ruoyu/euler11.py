#import
import numpy as np

#arrays
ar= np.loadtxt('data11.txt')

#vars
nrow,ncol=ar.shape
cp= 1
p=1

for i in range(nrow):
    for j in range(ncol):
        p=ar[i, j:j+4].prod()
        if p>cp:
            cp=p
        p=ar[i:i+4, j].prod()
        if p>cp:
            cp=p
        p=ar[i:i+4, j:j+4].diagonal().prod()
        if p>cp:
            cp=p
        p = 1
        if i > 2 and j < ncol-3:
            for k in range(4):
                p *= ar[i-k, j+k]
        if p>cp:
            cp=p
print(cp)
