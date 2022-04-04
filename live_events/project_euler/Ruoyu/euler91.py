'''
Observations:
(a) A lattice right triangle with the origin can have its right angle at the origin or somewhere else on the grid
Let's consider these cases separately
(b) When the right angle is at the origin, there are n ^ 2 possibilites, n being the grid size (50 in this case)
(c) When the right angle is somewhere else on the grid, we can loop through all possible points 1 to n in both x and y for point 1
slope(point 1, point 2) must -x/y
(d) Simplify slope(point 1, point 2) by using a gcd function
This allows all possible lattice points to be counted
Then we simply add -x to y and y to x until either x or y is less than 0 or greater than n
Then we go the other way and subract -x from y and y from x and use the same terminal condition as above

Approach:
Use Observation (b) to calculate case 1 and Observations (c) and (d) to calculate case 2
'''

#Vars
Grid = 50 #Grid dimensions (constant = 50)
Total = 0 #Right triangles
Slope = (0, 0) #Slope of line from origin to (x, y) in the form y / x

#User def functions
def Gcd(a, b) -> int:
    while True:
        if a % b == 0:
            return b
        a %= b
        if b % a == 0:
            return a
        b %= a

#Main
if __name__ == '__main__':
    Total = Grid ** 2 #Right angle at origin
    #Right angle not at origin
    for y in range(Grid + 1):
        for x in range(Grid + 1):
            if x != 0 or y != 0:
                if x == 0 or y == 0:
                    Total += Grid
                else:
                    tempx = x
                    tempy = y
                    temp = Gcd(x, y)
                    Slope = (-x // temp, y // temp)
                    Total -= 1
                    while tempx <= Grid and tempx >= 0 and tempy <= Grid and tempy >= 0:
                        Total += 1
                        tempx -= Slope[1]
                        tempy -= Slope[0]
                    tempx = x
                    tempy = y
                    Total -= 1
                    while tempx <= Grid and tempx >= 0 and tempy <= Grid and tempy >= 0:
                        Total += 1
                        tempx += Slope[1]
                        tempy += Slope[0]
    print(Total)
