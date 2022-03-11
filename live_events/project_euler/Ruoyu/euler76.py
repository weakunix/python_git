#METHOD 1
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
SumDict = {0: (0, 1), 1: (0, 1), 2: (0, 1, 1)} #Dict of previous f(n)
New = () #New f(n)

#Main
if __name__ == '__main__':
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

#METHOD 2
'''
Method 1 is great but it doesn't work for Euler 77
Thus Method 2 has been created:

Observations:
(a) Let f(n) return a dictionary of the number of sums using k and numbers >= k for 1 <= k <= n
For example, f(5) would be {1: 5, 2: 1, 3: 0, 4: 0, 5: 1}
Using numbers >= 1, there are 5 combinations: (1, 4), (1, 1, 3), (1, 1, 1, 2), (1, 1, 1, 1), (1, 2, 2)
Using numbers >= 2, there is 1 combination: (2, 3) since we cannot use 1
Using numbers >= 3 and 4, there are 0 combinations since we cannot use 1 or 2
Using numbers >= 5, there is 1 combination: (5)
(b) We define f(n) in such a way because it allows us to find f(n) using f(n - k)
(c) f(0) returns 1 no matter what since this is only the case when we try to write n as the sum of 1 number
(d) f(1) = {1: 1}, f(2) = {1: 1, 2: 1}
(e) To get f(n), we will loop through k where 1 <= k <= n and take the sum of f(n - k)'s elements with keys >= k to avoid multiple counting
(f) Observation (e) guarentees that the order of numbers will be increasing, thus each sum is only counted once

Approach:
Store all previous f(n) (defined in Observation (a)) and loop through all n where 3 <= n <= 100
Use Observation (e) to get each succeeding f(n)
'''

#Vars
SumDict = {1: {1: 1}, 2: {1: 1, 2: 1}} #Dict of previous f(n)
New = {} #New f(n)
Total = 0 #Total sums of 100

#Main
if __name__ == '__main__':
    for n in range(3, 101):
        New = {}
        for i in range(1, n + 1):
            count = 0
            try:
                temp = SumDict[n - i]
                for k in range(i, len(temp) + 1):
                    count += temp[k]
            except:
                count = 1
            New[i] = count
        SumDict[n] = New
    for i in New:
        Total += New[i]
    print(Total - 1)
