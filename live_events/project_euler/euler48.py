#vars
sumn = 0

#taking all numbers from 1 to 1000 powering them with themselves
for i in range(1, 1001):
    sumn += i ** i
    print(i)
sumn = str(sumn)
print(sumn[-10:])
