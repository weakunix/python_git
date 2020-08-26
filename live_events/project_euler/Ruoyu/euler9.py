found = False
for a in range(1, 334):
    for b in range(a, int((1000-a)/2)):
        c = 1000-a-b
        if a*a+b*b==c*c:
            found = True
            break
    if found:
        break
print("{} * {} * {} = {}".format(a, b, c, a*b*c))
