'''
Observations:
(a) The triangle must be isosceles (with sides c, c, 2a) and can be split down the middle to form a right triangle
(b) The sides must form a primitive pythagorean triple since 2a = c +- 1
(c) All primitive pythagorean triples can be written in the form (m^2 - n^2, 2mn, m^2 + n^2) for 0 < n < m
(d) c = m^2 + n^2, a = 2mn or m^2 - n^2
Let's consider these cases separately
When a = 2mn:
p = 2(m + n)^2
It only works when m^2 + n^2 - 4mn = +- 1
This can be solved using the quadratic formula and only when n is an integer less than m does this work
We terminate the program when 2(m + 1)^2 > 1 billion since the following case terminates faster
When a = m^2 - n^2:
p = 4m^2
It only works when 3n^2 - m^2 = +- 1
This can be solved since n^2 = (m^2 +- 1) / 3 and only when n is an integer does this work (n is automatically less than m)
We can terminate this testing when p > 1 billion

Approach:
Use Observations (a), (b), (c), and (d)
'''

#Imports
import math as albreto

#Vars
Total = 0 #Sum of perimeters of all equilateral triangles with integral side lengths and area
OneBil = 10 ** 9 #1 billion (const)
m = 1 #m
StillConsiderSecondCase = True #Is second case perimeter still in range (4m^2 <= 1 billion)

#User def functions
def SolveQuad(b, c, a = 1) -> set:
    d = albreto.sqrt(b ** 2 - 4 * a * c)
    if d % 1 != 0:
        return set()
    d = int(d)
    Possible = {(-b + d) / (2 * a), (-b - d) / (2 * a)}
    Sols = set()
    for i in Possible:
        if i % 1 == 0:
            Sols.add(int(i));
    return Sols

#Main
if __name__ == '__main__':
    while True:
        m += 1
        print(m)
        if StillConsiderSecondCase:
            p = 4 * m ** 2
            if p > OneBil:
                StillConsiderSecondCase = False
            elif m % 3 != 0:
                temp = (m ** 2 - 1) // 3
                if albreto.sqrt(temp) % 1 == 0:
                    print(p, m)
                    Total += p
        if 2 * (m + 1) ** 2 > OneBil:
            break
        Sols = SolveQuad(-4 * m, m ** 2 + 1).union(SolveQuad(-4 * m, m ** 2 - 1))
        for n in Sols:
            p = 2 * (m + n) ** 2
            if p <= OneBil and n < m:
                print(p, m, n)
                Total += p
    print(Total)
