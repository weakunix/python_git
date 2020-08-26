import numpy as np
def ispalin(x):
    n = int(np.log10(x)) + 1
    isp = True
    for i in range(0, int(n / 2) + 1):
        num1 = x % 10 ** (i + 1)
        num1 = int(num1 / 10 ** i)
        num2 = x % 10 ** (n - i)
        num2 = int(num2 / 10 ** (n - i - 1))
        if num1 != num2:
            isp = False
            break
    return isp

b = 0
a1 = 0
a2 = 0
s = 999 + 999
m = 0
while s >= 200 and s > m:
    n1 = int(s / 2)
    n2 = s - n1
    while n1 > 99 and n2 < 1000:
        #print('trying {}*{}'.format(n1, n2))
        if ispalin(n1 * n2):
            if n1 * n2 > b:
                b = n1 * n2
                a1 = n1
                a2 = n2
                m = np.sqrt(b)*2
            break
        n1 -= 1
        n2 += 1
    s -= 1
if b > 0:
    print('{}={}*{}'.format(b,a1,a2))
else:
    print('no palindrome found')
