#reading p042_words.txt for words
fp = open('p042_words.txt', 'r')
words = fp.readline()
words = words.split(',')
words = [x[1:-1] for x in words]

#vars
count = 0
value = 0
trinum = 0
count2 = 0
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

#trying all words
for i in words:
    value = 0
    for k in i:
        value += avalue[k]
    trinum = 0
    count2 = 0
    while trinum < value:
        count2 += 1
        trinum = count2 * (count2 + 1) / 2
    if trinum == value:
        count += 1
print(count)
