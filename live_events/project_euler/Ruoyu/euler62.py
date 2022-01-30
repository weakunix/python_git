'''
Observations:

N | N ^ 3 mod 10
--------------
0 | 0
1 | 1
2 | 8
3 | 7
4 | 4
5 | 5
6 | 6
7 | 3
8 | 2
9 | 9

All digits can occur

Possibilities:

Loop through 1 <= i to as much as possible and take i ^ 3
After digits change, calculate permutations in the set of cubes
Reset if none are found
'''

#Vars
Count = 0 #Count
CubeSet = set() #Set of cubes
CurrentDigits = 1 #Current digits of cubes

#User def functions
def DigitCount(n) -> list:
    l = [0 for i in range(10)]
    for i in str(n):
        l[int(i)] += 1
    return l

def IsPermutation(a, b) -> bool:
    return DigitCount(a) == DigitCount(b)

def CalculatePermutations() -> list:
    temp = list(CubeSet)
    for i in range(len(temp)):
        RangeMin = i
        i = temp[i]
        PermutationList = [i]
        for k in range(RangeMin + 1, len(temp)):
            k = temp[k]
            if IsPermutation(i, k):
                PermutationList.append(k)
        if len(PermutationList) >= 5:
            PermutationList.sort()
            print(PermutationList)
            return PermutationList
    return None

#Main
if __name__ == '__main__':
    while True:
        Count += 1
        temp = Count ** 3
        if len(str(temp)) > CurrentDigits:
            if CalculatePermutations() != None:
                break
            CurrentDigits += 1
            CubeSet = set()
        CubeSet.add(temp)
