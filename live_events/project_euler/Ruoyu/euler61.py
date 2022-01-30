'''
Observations:
Numbers must be [abcd, cdef, efgh, ghij, ijkl,  klab]
Number [cdef] must be perfect square
Last number is decided
First and third digit of any number cannot be 0

Possibilites:
BFI through 4 digit perfect squares as there are only 68
Instead of going 3 > 4 > 5 > 6 > 7 > 8, we can go 4 > 5 > 6 > 7 > 8 > 3

Or

Go backward 8 > 7 > 6 > 5 > 4 > 3 since 8 has the least amount of elements

Or

Consier all numbers that are [abcdefghijkl]
'''

#Vars
Oct = []
OtherLists = []

#User def functions
def TriNum(n) -> int:
    return n * (n + 1) // 2

def PentNum(n) -> int:
    return n * (3 * n - 1) // 2

def HexNum(n) -> int:
    return n * (2 * n - 1)

def HepNum(n) -> int:
    return n * (5 * n - 3) // 2

def OctNum(n) -> int:
    return n * (3 * n - 2)

def GenLists() -> None:
    #Triangle
    for i in range(45, 141):
        if str(TriNum(i))[2] != '0':
            OtherLists.append((TriNum(i), 3))

    #Square
    for i in range(32, 100):
        if str(i ** 2)[2] != '0':
            OtherLists.append((i ** 2, 4))

    #Pentagonal
    for i in range(26, 82):
        if str(PentNum(i))[2] != '0':
            OtherLists.append((PentNum(i), 5))

    #Hexagonal
    for i in range(23, 71):
        if str(HexNum(i))[2] != '0':
            OtherLists.append((HexNum(i), 6))

    #Heptagonal
    for i in range(21, 64):
        if str(HepNum(i))[2] != '0':
            OtherLists.append((HepNum(i), 7))

    #Octagonal
    for i in range(19, 59):
        if str(OctNum(i))[2] != '0':
            Oct.append(OctNum(i))

def IsCyclical(a, b) -> bool:
    a = str(a)
    b = str(b)
    return a[2:] == b[:2]


def GenerateCycle(NumList, TypesRemain) -> list:
    if len(TypesRemain) == 1:
        temp = int(str(NumList[-1])[2:] + str(NumList[0])[:2])
        if (temp, list(TypesRemain)[0]) in OtherLists:
            return NumList + [temp]
        return None
    for i in OtherLists:
        temp = NumList[-1]
        if i[1] in TypesRemain:
            if IsCyclical(temp, i[0]):
                temp = TypesRemain.copy()
                temp.remove(i[1])
                temp = GenerateCycle(NumList + [i[0]], temp)
                if temp != None:
                    return temp
    return None

#Main
if __name__ == '__main__':
    GenLists()
    for o in Oct:
        temp = GenerateCycle([o], {3, 4, 5, 6, 7})
        if temp != None:
            print(temp, sum(temp))
            break
