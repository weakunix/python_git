a = [i for i in range(4000000)]; b = 0
for i in range(len(a)):
    for x in range(1, 3):
        b += a[i-x]
print(b)