'''
Observations:
Call the inner nodes a, b, c, d, e

Total = 2 * (a + b + c + d + e) + 55 - (a + b + c + d + e)

Min sum of each line = 14
Max sum of each line = 19

10 must be on the outside
In other words, a, b, c, d, e != 10

Biggest solution should have 6 starting

We must have 6, 7, 8, 9, 10 on the outside and 1, 2, 3, 4, 5 on the inside

Fix node 6
Sum of each line must be 14 (15 doesn't work)

10 is the worst node since it only adds 1
9, 8, and 7 are better (in that order)

Always have the first line be 6 5 3 since 65... is the largest possible start

Approach:
Math it!
No programming needed, just draw a diagram and try to put in the largest possible numbers in each node
'''

#Main
if __name__ == '__main__':
    print('6531031914842725')
