listOtoOneHunnit = [x for x in range(1,101)]

def recursive(a = None, n = None) -> None:
    if a == None and n == None:
        a = 1
        n = 1
    elif a == len(listOtoOneHunnit):
        print(n)
        return
    recursive(a + 1, n + listOtoOneHunnit[a])

recursive()