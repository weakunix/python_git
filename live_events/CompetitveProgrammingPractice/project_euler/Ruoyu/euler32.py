#vars
pand = []
p = 0
nums = []

#trying every number
for i in range(1, 10000):
    for k in range(1, 10000):
        nums = []
        p = str(i) + str(k) + str(i * k)
        if len(p) > 9:
            break
        if len(p) == 9:
            for d in p:
                if d not in nums and d != '0':
                    nums.append(d)
                else:
                    p = False
                    break
            if p != False and i * k not in pand:
                pand.append(i * k)
print(sum(pand))
