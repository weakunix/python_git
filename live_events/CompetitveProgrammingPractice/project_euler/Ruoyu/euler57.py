#vars
frac = [1, 2] #current fraction
count = 0 #number of expansions where numerator > denominator

#testing first 1000  expansions for numerator > denominator
for i in range(1000):
    #consider fraction
    print(f'{frac[0] + frac[1]} / {frac[1]}')
    if len(str(frac[0] + frac[1])) > len(str(frac[1])):
        count += 1
    #2 + current fraction
    frac = [frac[1], 2 * frac[1] + frac[0]]
print(count)
