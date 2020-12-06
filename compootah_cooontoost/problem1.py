def functikon(x):
    if x>=3:
        return 2*functikon(x-1) + functikon(x-2)
    elif x == 2:
        return 0
    elif x == 1:
        return 2

print(functikon(6))