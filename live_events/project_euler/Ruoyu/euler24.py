#vars
digit = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
p = ""
n = 1000000
count = 0

#user def functions
def factorial(n):
    ans = 1
    n = 10 - n
    for i in range(1, n + 1):
        ans *= i
    return ans


#find each number
for i in range(1, 10):
    count = 0
    while n > factorial(i):
        count += 1
        n -= factorial(i)
    p += str(digit.pop(count))
p += str(digit[0])
print(p)
