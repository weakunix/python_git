# open a file to read
fp = open('data13.txt', 'r')
tot = 0
for line in fp:
    tot += int(line[:-1])
tot = str(tot)
print(tot[0:10])
