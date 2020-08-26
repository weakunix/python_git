#vars
sumn = []
fact = 0

#user def functions
#factorial
def factorial(n):
    fact = 1
    for i in range(1, n + 1):
        fact *= i
    return fact

#trying digit factorials
for i in range(3, 2999999):
    fact = 0
    for k in str(i):
        fact += factorial(int(k))
        if fact > i:
            break
    if fact == i:
        sumn.append(i)
print(sumn, sum(sumn))
