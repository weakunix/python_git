#names txt file
fp = open('p022_names.txt', 'r')
names = fp.readline()
names = names.split(',')
names = [x[1:-1] for x in names]
names.sort()

#vars
count = 0
nsum = 0
nvalue = 0

#dicts
avalue = {  'A': 1,
            'B': 2,
            'C': 3,
            'D': 4,
            'E': 5,
            'F': 6,
            'G': 7,
            'H': 8,
            'I': 9,
            'J': 10,
            'K': 11,
            'L': 12,
            'M': 13,
            'N': 14,
            'O': 15,
            'P': 16,
            'Q': 17,
            'R': 18,
            'S': 19,
            'T': 20,
            'U': 21,
            'V': 22,
            'W': 23,
            'X': 24,
            'Y': 25,
            'Z': 26}

#finding name scores
for i in names:
    nvalue = 0
    count += 1
    for k in i:
        nvalue += avalue[k]
    nsum += nvalue * count
print(nsum)
