import math

def f(x):
    if x >= 6 and x % 2 == 0:
        return f(x/2) + 1
    elif x >= 1 and x % 2 != 0:
        return f(math.floor(x/2)) - 3
    else:
        return (x*3) + 4

print(f(28))