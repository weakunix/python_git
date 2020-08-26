#imports
import euler21 as e21 #divisor sum function from euler21

#vars
ds = 0
nasum = 0
asum = False

#lists
a = []


#find abundant numbers
for i in range(1, 28124):
    ds = e21.divisor_sum(i)
    if ds > i:
        a.append(i)

#find sum of numbers which cannot be written as the sum of 2 abundant numbers
for i in range(1, 28124):
    print(i)
    asum = False
    for k in a:
        if k >= i:
            break
        if i - k in a:
            asum = True
            break
    if asum == False:
        nasum += i
print(nasum)
