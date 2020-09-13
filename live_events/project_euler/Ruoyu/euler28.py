#vars
spiral = -1
nis = 0
dnums = []
n = 0
dsum = 0
count = 0

#user def functions
def numbers_in_spiral(spiral):
    if spiral == 1:
        return 1
    return 4 * (spiral - 1)

def diagonal_numbers(spiral):
    if spiral == 1:
        return [1]
    return [spiral - 1, 2 * (spiral - 1), 3 * (spiral - 1), 4 * (spiral - 1)]
    

#find sum of numbers on diagonals in 1001 by 1001 spiral
while spiral != 1001:
    count = 0
    spiral += 2
    nis = numbers_in_spiral(spiral)
    dnums = diagonal_numbers(spiral)
    for i in range(1, nis + 1):
        n += 1
        count += 1
        if count in dnums:
            dsum += n
print(dsum)
