'''
Observations:
(a) First, let's generate all the consecutive square sums below 10 ^ 8
We observe that there can be anywhere from 2 to 668 consecutive squares to sum up to possible numbers (this is because 1 ^ 2 + 2 ^ 2 + 3 ^ 2 + ... + 668 ^ 2 < 10 ^ 8 but + 669 ^ 2 > 10 ^ 8)
In other words, this will be in the form k ^ 2 + (k + 1) ^ 2 + (k + 2) ^ 2 + ... + (k + l - 1) ^ 2 where l <= 668
For every k ^ 2 + (k + 1) ^ 2 + (k + 2) ^ 2 + ... + (k + l - 1) ^ 2, we can get (k + 1) ^ 2 + (k + 2) ^ 2 + ... + (k + l) ^ 2 by subtracting k ^ 2 and adding (k + l) ^ 2
We do this and add each result to the set until the sum >= 10 ^ 8

Approach:
We can use Observation (a) to generate a set of all consecutive square sums below 10 ^ 8
Then, we can test each one to see if they are a palindrome by looping through each digit of the number
'''

#Vars
ConsecutiveSquareSums = set() #Set of consecutive square sums below 10 ^ 8
Total = 0 #Sum of consecutive square sums that are palindromic

#User def functions
def IsPalin(n) -> bool:
     n = str(n)
     for i in range((len(n) + 1) // 2):
         if n[i] != n[-(i + 1)]:
             return False
     return True

#Main
if __name__ == '__main__':
    for l in range(2, 669):
        temp = 0
        for i in range(1, l + 1):
            temp += i ** 2
        count = 1
        while temp < 10 ** 8:
            ConsecutiveSquareSums.add(temp)
            temp -= count ** 2
            temp += (count + l) ** 2
            count += 1
    for i in ConsecutiveSquareSums:
        if IsPalin(i):
            Total += i
    print(Total)
