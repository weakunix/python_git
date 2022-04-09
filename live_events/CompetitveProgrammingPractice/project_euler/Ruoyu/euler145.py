'''
Observations:
(a) Observe that adding n and reverse(n) gets
a1 a2       a3       a4       ... ax
ax a(x - 1) a(x - 2) a(x - 3) ... a1
(b) Pairs form and we shall call them pairs 1, 2, 3, 4, ... x
(c) Observe that pairs 2 and x - 1 can never carry
This is because pair 1 = pair x which is always odd and adding one will make it even
(d) Observe that if we have pair p = aj + aj (j > 1 where j is an integer), we require pair p + 1 and p - 1 to carry
(e) Observe which cases require other carries and which cases are impossible
(f) The number of ways we can sum two numbers to get n if n is:
Odd, single digit: 30
Odd, double digit: 20
Even (single and double) digit: 25
Odd (single or double digit) without 0: 20 (for the first and last digit of each number)
Even (single or double digit) with two of the same number: 5 (for mid number case)

Approach:
Math it!
Use the Observations above and try cases with x digits use Observation (f) to calculate how many solutions there are
Sum them all up
'''

#Main
if __name__ == '__main__':
    print(0 + 20 + 100 + 600 + 0 + 18000 + 50000 + 540000 + 0)
