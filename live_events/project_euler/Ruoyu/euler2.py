p = 1
pp = 1
t=0
ti=0
n=0
#for i in range(1000):
while p<4000000:
    n += 1
    print('{}{}'.format(p, '*' if p%2==0 else ''))
    if p%2==0:
        t += p
        ti += 1
    tmp = p+pp
    pp = p
    p = tmp
print('n={} n_even={} sum_even={}'.format(n, ti, t))
