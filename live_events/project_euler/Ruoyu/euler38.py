#vars
n = 0
maxn = 0
alld = ''

#trying all numbers for largest pandigital multiples
for i in range(1, 10000):
    count = 0
    alld = ''
    while len(alld) < 9:
        count += 1
        alld += str(i * count)
        if len(alld) > 9:
            count = False
    if count:
        count = True
        for k in range(1, 10):
            k = str(k)
            if k not in alld:
                count = False
                break
        if count and int(alld) > maxn:
            maxn = int(alld)
print(maxn)
