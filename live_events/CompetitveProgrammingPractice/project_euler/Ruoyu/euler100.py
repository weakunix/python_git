'''
Observations:
(a) Do algebra and let x = 2b - 1 and y = 2n - 1
We get a negative pell's equation: y^2 - 2x^2 = -1
(b) We can use continuous fractions to find solutions to this pell's equation by finding every other convergent of sqrt(2) (in the form y/x) in the following way
If Cn = 1 + p/q, C(n + 1) = 1 + 1 / (2 + p / q)

Approach:
We can use Observation (b) and get every other convergent to get x and y
Then we can use Observation (a) to get b and n
When n >= 10 ^ 12 we get b
'''

#Imports
import math as albreto

#Vars
Convergent = [2, 5]
TenToTwelfth = 10 ** 12

#User def functions
def NextConvergent(c) -> list:
    return [c[1], 2 * c[1] + c[0]]

#Main
if __name__ == '__main__':
    while True:
        Convergent = NextConvergent(NextConvergent(Convergent))
        x = Convergent[1]
        y = Convergent[0] + Convergent[1]
        if (y + 1) // 2 >= TenToTwelfth:
            print((x + 1) // 2)
            break

