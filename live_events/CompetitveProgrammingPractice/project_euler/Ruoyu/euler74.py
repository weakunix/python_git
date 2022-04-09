'''
Observations:

Approach:
BFI by storing the factorials of each digit and looping up to 1 million
'''

#Vars
Total = 0 #Total chains with a starting number < 1 million containing exactly 60 non repeating terms
Factorials = {0: 1} #Dict of factorials from 0 to 9 (for each digit)

#User def functions
def DigitFactorial(n) -> int:
    count = 0
    for i in str(n):
        count += Factorials[int(i)]
    return count

#Set variables
temp = 1
for i in range(1, 10):
    temp *= i
    Factorials[i] = temp

#Main
if __name__ == '__main__':
    for i in range(2, 10 ** 6):
        print(i)
        temp = {i}
        count = 1
        while len(temp) == count:
            i = DigitFactorial(i)
            temp.add(i)
            count += 1
        if len(temp) == 60:
            Total += 1
    print(Total)
