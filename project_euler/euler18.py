#vars
maxsum = 0
rows = []
numsum = [75]
column = 0

#reading data_e18.txt
with open('data_e18.txt','r') as fp:
   for line in fp:
      row = line.split()
      row = [int(r) for r in row]
      rows.append(row)

#trying all routes
for i in range(2 ** 14):
    numsum = [75]
    column = 0
    for count in range(1, 15):
        if i & 1 == 1:
            column += 1
        numsum.append(rows[count][column])
        i >>= 1
    numsum = sum(numsum)
    if numsum > maxsum:
        maxsum = numsum
print(maxsum)
