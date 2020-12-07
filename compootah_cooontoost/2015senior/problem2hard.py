def smol(x):
    return round(x)

def f(x):
    if x >= 8:
        return f(smol(x/2)-2)+3
    elif 2 <= x < 8:
        return f(x-1) + 2
    elif x<2:
        return x+4

print(f(f(f(f(16)))))