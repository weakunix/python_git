#vars
prod = 1
dsum = 0


#100!
for i in range(1, 101):
    prod *= i

#digit sum
prod = str(prod)
for i in prod:
    i = int(i)
    dsum += i
print(dsum)
