def f(x,y):
    if x > y:
        return f(x - 3, y - 1) + 1
    elif x == y:
        return f(x-1, y) - 2
    elif x < y:
        return 2*x-y

print(f(20,10))