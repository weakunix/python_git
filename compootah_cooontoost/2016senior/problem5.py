a = 20
b = 4
c = 2
d = 100
e = 3

for i in range(1, 5):
    try:
        if a/i>d/b:
            a -= 2
        else:
            d -= 20
    except ZeroDivisionError:
        print("ERROR")
    if b+3*i<a*c:
        b+= 1
    else:
        c+=1
    if c**e > e**c:
        c+= 1
    else:
        e+= 1

    print(a)
    print(b)
    print(c)
    print(d)
    print(e)
    print("--")

print(4*(a/e + b/c) - a/(b+2) + d ** 2 / a * 2)