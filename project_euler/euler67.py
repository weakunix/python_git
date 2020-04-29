import datetime as dt

#vars
maxsum = 0
rows = []
numsum = [75]
column = 0

#reading data_e18.txt
with open('p067_triangle.txt','r') as fp:
   for line in fp:
      row = line.split()
      row = [int(r) for r in row]
      rows.append(row)

#trying all routes
t1 = dt.datetime.now()
for i in range(2 ** 99):
    numsum = [59]
    if i % 1000 == 0:
        passed = (dt.datetime.now() - t1).total_seconds()
        print('{}: max={} elapsed={}s'.format(i,maxsum,passed))
    column = 0
    for count in range(1, 100):
        if i & 1 == 1:
            column += 1
        numsum.append(rows[count][column])
        i >>= 1
    numsum = sum(numsum)
    if numsum > maxsum:
        maxsum = numsum
print(maxsum)
