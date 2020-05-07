#vars
rows = []
row = []

#reading data_e18.txt
with open('p067_triangle.txt', 'r') as fp:
    for line in fp:
        row = line.split()
        row = [int(r) for r in row]
        rows.append(row)

#finding largest route
for i in range(-98, 1):
    row = []
    i = -i
    for k in range(i + 1):
        if rows[-1][k] > rows[-1][k + 1]:
            row.append(rows[-1][k] + rows[-2][k])
        else:
            row.append(rows[-1][k + 1] + rows[-2][k])
    rows.pop()
    rows.pop()
    rows.append(row)
print(rows[0][0])
