'''
Observations:
We want the largest n / phi(n)
This is maximized when n is as big as possible and phi(n) is as small as possible
phi(n) is minimized when the number of prime factors of n is maximized

Approach:
Math it!
We fit as many prime factors as we can into n before exceeding 1 million
Then, ifpossible, we multiply the product by another prime factor (maybe 2, 3, etc.) to maximize n
'''

if __name__ == '__main__':
    print(2 * 3 * 5 * 7 * 11 * 13 * 17)
