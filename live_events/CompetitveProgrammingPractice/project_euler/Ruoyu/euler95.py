'''
Observations:
(a) We can split the problem into two parts
(b) First, we must find the proper divisor sum of all numbers 2 to 1 million
We can do this by looping through all numbers 2 to sqrt(n) and adding d and n / d (where d is a divisor) to the total
Remember that 1 is also a proper divisor so we should also add 1
Also we must test that d != n / d or else we would be multiple counting d
(c) Then we can loop through the dictionary of proper divisor sums and try chains
Invalidate the chain if it reaches 1 or exceeds 1 mil since there will be an invalid key
Find the longest chain and smallest element

Approach:
Using Observation (a), we can use Observations (b) and (c) to find the smallest element of the longest amicable chain
'''

#Imports
import math as albreto

#Vars
ProperDivSums = {} #Dict of n : PropDivSum(n)
CurChain = set() #Current chain
LongestChain = (0, 0) #Longest chain (len, smallest elem)

#User def functions
def GetDivSum(n) -> int:
    DivSum = 1
    for i in range(2, int(albreto.sqrt(n)) + 1):
        if n % i == 0:
            temp = n // i
            DivSum += i
            if i != temp:
                DivSum += temp
    return DivSum

#Main
if __name__ == '__main__':
    for i in range(2, 10 ** 6 + 1):
        if i % 1000 == 0:
            print(i)
        ProperDivSums[i] = GetDivSum(i)
    for i in ProperDivSums:
        CurChain = set()
        temp = i
        count = 0
        while temp not in CurChain:
            CurChain.add(temp)
            try:
                temp = ProperDivSums[temp]
            except:
                break
        if temp == i and (len(CurChain) > LongestChain[0] or (len(CurChain) == LongestChain[0] and i < LongestChain[1])):
            LongestChain = [len(CurChain), i]
    print(LongestChain)
