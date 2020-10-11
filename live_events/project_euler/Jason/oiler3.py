'''
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
'''

#do it like a binary tree

arrayOfFactors = []

def factorize(inpt):
    print(inpt)
    for i in range(inpt):
        if inpt % (i + 1) == 0:
            print(f"factor! {str(inpt / (i + 1))}")
            arrayOfFactors.append(int(inpt / (i + 1)))

print(factorize(600851475143))

matchedFactors = []

if len(arrayOfFactors) % 2 == 0:
    #is even
    for i in range(int(len(arrayOfFactors) / 2) - 1):
        matchedFactors.append([arrayOfFactors[i], arrayOfFactors[len(arrayOfFactors) - 1 - i]])

print(matchedFactors)
