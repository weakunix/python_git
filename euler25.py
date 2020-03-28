#vars
n1 = '1'
n2 = 1
sumn = 0
count = 2


#find first 1000 digit fibonacci number
while len(n1) < 1000:
    n1 = int(n1)
    count += 1
    sumn = n1 + n2
    n2 = n1
    n1 = str(sumn)
print(count)

