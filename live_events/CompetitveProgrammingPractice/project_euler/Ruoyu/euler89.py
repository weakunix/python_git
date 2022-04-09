'''
Observations:
(a) All rules can be ignored since they are followed when we try to use as few characters as possible
This is because we will always prefer larger numbers over smaller (i.e. M better than C)
We also want to use as many big numbers as possible so we will not equal or exceed M, C, or X with smaller denominations
D, L, and V also are natrually limited to at most 1 occurrence since two of D, L, or V could be replaced with a M, C, or X respectively
(b) Subtractive combinations are always better than normal combinations for the same number (i.e. IX better than XIIII)

Approach:
We first can convert all roman numerals to arabic numerals by looping through the roman numeral
We can use a dictionary
In this dictionary, we will include subtractive combinations

We can then convert the arabic numeral back into a roman numeral
Since we are only interested in the length saved, we only have to consider then length of each number (i.e. 100 = C which is length 1 and 4 = IV which is length 2)
Those that are subtractive combinations have length 2 and can only be used once
We must be sure to break the loop when one is used and move on to the next character

We can compare the length of the original roman numeral with the new roman numeral length
'''

#Vars
RomanNums = [] #List of Roman numerals
RomanToArabDict = {
                'M': 1000,
                'CM': 900,
                'D': 500,
                'CD': 400,
                'C': 100,
                'XC': 90,
                'L': 50,
                'XL': 40,
                'X': 10,
                'IX': 9,
                'V': 5,
                'IV': 4,
                'I': 1
                } #Dict of Roman numerals mapped to Arabic numerals in the order largest to smallest
ArabToRomanLenDict = {a: len(r) for r, a in RomanToArabDict.items()} #Dict of Arabic numerals mapped to the length of Roman numerals in the order of largest to smallest
CharSaved = 0 #Characters saved

#User def functions
def RomanToArab(r) -> int:
    count = 0
    for i in RomanToArabDict:
        while True:
            if r[:len(i)] == i:
                r = r[len(i):]
                count += RomanToArabDict[i]
                if len(r) == 0:
                    return count
            else:
                break

def ArabToRomanLen(n) -> int:
    count = 0
    for i in ArabToRomanLenDict:
        while True:
            if n >= i:
                n -= i
                count += ArabToRomanLenDict[i]
                if n == 0:
                    return count
                if ArabToRomanLenDict[i] == 2:
                    break
            else:
                break

#Read file
with open('p089_roman.txt', 'r') as f:
    for line in f:
        RomanNums.append(line.strip('\n'))

#Main
if __name__ == '__main__':
    for i in RomanNums:
        CharSaved += len(i) - ArabToRomanLen(RomanToArab(i))
    print(CharSaved)
