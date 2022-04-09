'''
Observations:
(a) The shortest straight path of a box is sqrt(z ^ 2 + (x + y) ^ 2) where 1 <= x <= y <= z <= M
(b) To reduce calculations, let w = x + y
Now we have sqrt(z ^ 2 + w ^ 2) and we can BFI
(c) Everytime we must add w // 2 - max(i - M - 1, 0) which basically means:
If i <= M, w // 2
Else w // 2 - (i - M - 1) to remove cases where y > M

Approach:
Use Observations (a), (b), and (c) to BFI
'''

#Imports
import math as albreto

#Vars
M = 0 #M
IntPaths = 0 #Number of integer shortest paths

#Main
if __name__ == '__main__':
    while IntPaths < 10 ** 6:
        print(IntPaths)
        M += 1
        temp = M ** 2
        for i in range(2, 2 * M + 1):
            if albreto.sqrt(temp + i ** 2) % 1 == 0:
                IntPaths += i // 2 - max(i - M - 1, 0)
    print(M)
