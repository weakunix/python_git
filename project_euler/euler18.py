#vars
maxsum = 0
count = 0
rows = []
numsum = [75]

#reading data_e18.txt
with open('data_e18.txt','r') as fp:
    for line in fp:
        row = line.split()
        row = [int(r) for r in row]
        rows.append(row)

#try every route
for i in range(1, 2 ** 14 + 1):
    numsum = [75]
    count = 0
    if i > 2 ** 13:
        count += 1
        i -= 2 ** 13
    numsum.append(rows[1][count])
    if i > 2 ** 12:
        count += 1
        i -= 2 ** 12
    numsum.append(rows[2][count])
    if i > 2 ** 11:
        count += 1
        i -= 2 ** 11
    numsum.append(rows[3][count])
    if i > 2 ** 10:
        count += 1
        i -= 2 ** 10
    numsum.append(rows[4][count])
    if i > 2 ** 9:
        count += 1
        i -= 2 ** 9
    numsum.append(rows[5][count])
    if i > 2 ** 8:
        count += 1
        i -= 2 ** 8
    numsum.append(rows[6][count])
    if i > 2 ** 7:
        count += 1
        i -= 2 ** 7
    numsum.append(rows[7][count])
    if i > 2 ** 6:
        count += 1
        i -= 2 ** 6
    numsum.append(rows[8][count])
    if i > 2 ** 5:
        count += 1
        i -= 2 ** 5
    numsum.append(rows[9][count])
    if i > 2 ** 4:
        count += 1
        i -= 2 ** 4
    numsum.append(rows[10][count])
    if i > 2 ** 3:
        count += 1
        i -= 2 ** 3
    numsum.append(rows[11][count])
    if i > 2 ** 2:
        count += 1
        i -= 2 ** 2
    numsum.append(rows[12][count])
    if i > 2:
        count += 1
        i -= 2
    numsum.append(rows[13][count])
    if i > 1:
        count += 1
    numsum.append(rows[14][count])
    numsum = sum(numsum)
    if numsum > maxsum:
        maxsum = numsum
print(maxsum)

