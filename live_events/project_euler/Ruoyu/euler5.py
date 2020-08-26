def lcm(x, y):
    a = x
    b = y
    a = a % b
    while a != 0:
        c = b % a
        b = a
        a = c
    l = x * y / b
    return l
l = 1
for num in range(2, 21):
    l = lcm(l, num)
print(l)
