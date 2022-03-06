'''
Observations:
(a) Let f(n) return a tuple of the number of sums with k integers from 0 to n
For example, f(5) = (0, 1, 2, 2, 1, 1)
The 0th index represents how many ways we can write 5 with 0 integers (0)
The 1st index represents how many ways we can write 5 with 1 integer (1)
So on...
(b) f(0) = (0, 1), f(1) = (0, 1), f(2) = (0, 1, 1)
(c) To solve f(n), we must recognize that n can be written as 2, 3, 4, ..., n positive integers
If n were to be written as 2 positive integers, it would be 1 + a, 1 + b where a + b = n - 2
To find all combinations (a, b) is the sum f(n - 2) UP TO THE 2ND INDEX

Similarly, if n were to be written as 3 positive integers, it would be 1 + a, 1 + b, 1 + c where a + b + c = n - 3
All combinations (a, b, c) is the sum f(n - 3) UP TO THE 3RD INDEX

In general, if n were to be written as k positive integers, the solution is f(n - k) UP TO THE kTH INDEX

Approach:
We store all f(n) defined in Observation (a)
We can find the succeeding f(n) by using Observation (c)
'''

#Vars
SumDict = {0: (0, 1), 1: (0, 1), 2: (0, 1, 1)} #Dict of previous sums

#Main
for n in range(3, 101):
    New = [0, 1]
    for k in range(2, n + 1):
        count = 0
        for a, b in enumerate(SumDict[n - k]):
            if a > k:
                break
            count += b
        New.append(count)
    SumDict[n] = tuple(New)
print(sum(New) - 1)
