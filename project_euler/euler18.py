#vars
maxsum = 0
count = 0

#lists
rows = []
numsum = [75]
l = []

#read number triangle txt file
with open('data_e18.txt','r') as fp:
    for line in fp:
        row = line.split()
        row = [int(r) for r in row]
        rows.append(row)

#try every route
for a in range(0, 2):
    for b in range(0, 2):
        for c in range(0, 2):
            for d in range(0, 2):
                for e in range(0, 2):
                    for f in range(0, 2):
                        for g in range(0, 2):
                            for h in range(0, 2):
                                for i in range(0, 2):
                                    for j in range(0, 2):
                                        for k in range(0, 2):
                                            for l in range(0, 2):
                                                for m in range(0, 2):
                                                    for n in range(0, 2):
                                                        count = 0
                                                        numsum = [75]
                                                        l = [a, b, c, d, e, f, g, h, i, j, k, l, m, n]
                                                        for v in range(14):
                                                            count += l[v]
                                                            v += 1
                                                            numsum.append(rows[v][count])
                                                        numsum = sum(numsum)
                                                        if numsum > maxsum:
                                                            maxsum = numsum
print(maxsum)
