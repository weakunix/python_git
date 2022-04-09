#vars
ndigits = 1
n = ''
sumn = 0
num = 0

#find biggest number to test
while sumn == 0:
    ndigits += 1
    if 10 ** (ndigits - 1) > 9 ** 5 * ndigits:
        ndigits -= 1
        for i in range(1, ndigits + 1):
            n += '9'
        n = int(n)
        break

#try all numbers less than biggest number
for i in range(10, n + 1):
    print(i)
    num = 0
    for d in str(i):
        d = int(d)
        d **= 5
        num += d
    i = int(i)
    if num == i:
        sumn += int(i)
print(sumn)
