#lists
terms = []
num = 0

#trying each a ** b for 2 <= a <= 100 and 2 <= b <= 100
for a in range(2, 101):
    for b in range(2, 101):
        num = a ** b
        if num not in terms:
            terms.append(num)
print(len(terms))
