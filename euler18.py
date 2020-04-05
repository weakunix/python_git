#vars
maxsum = 0
numsum = 0

#lists
rows = []

#read number triangle txt file
with open('data_e18.txt','r') as fp:
    for line in fp:
        row = line.split()
        row = [int(r) for r in row]
        rows.append(row)

#try every route
for i in range(1, 15):
    for k in range(0, 2):

