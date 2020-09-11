import random

arraytosort = [random.randint(0,10000) for x in range(random.randint(0, 100))]

def sorts() -> bool:
    x = 0
    for i in range(len(arraytosort) - 1):
        if arraytosort[i] < arraytosort[i + 1]:
            x += 1
    return True if x == 0 else False

while not sorts():
    for i in range(len(arraytosort) - 1):
        if arraytosort[i] < arraytosort[i + 1]:
            a = arraytosort[i]
            arraytosort[i] = arraytosort[i + 1]
            arraytosort[i + 1] = a

print(arraytosort)