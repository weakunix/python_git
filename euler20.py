'''
Euler 20

1. Find 100! with for loop
2. Convert to string and add all digits in for loop
'''

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
