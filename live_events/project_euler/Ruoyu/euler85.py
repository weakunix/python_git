'''
Observations:
(a) Let x and y be the demensions of the rectangular grid
(b) Let f(x, y) be the rectangle count
(c) We can see that f(x, y) = f(x - 1, y) + f(x, y - 1) - f(x - 1, y - 1) + x * y
This can be proven by the following:
The rectangles in an x by y rectangular grid can either contain or not contain the top left square
The ones that do not contain the top left square can be found in the grid (x - 1) by y or x by (y - 1) (thus the f(x - 1, y) + f(x, y - 1))
We must remove the rectangle count of the grid (x - 1) by (y - 1) because it has been double counted (thus the -f(x - 1, y - 1))
Finally, the count of the rectangles that do contain the top left square is x * y (the x * y at the end of the equation)
(d) We can let x >= y to avoid multiple counting and optimization

Approach:
Keep incrementing y and increment x starting from y so we can keep Observation (d) true
Keep a dictionary of previous rectangle counts so we can use Observation (c)
We terminate the program when the rectangle count of x by y is greater than 2 million and x == y
NOTE
Because we use Observation (d) and keep x >= y, sometimes we will run into index errors when x - 1 < y (a simple check and sort will fix this)
Also, we do not store 0 by y or x by 0 grids so we will have to manually check for those cases
'''

#Vars
ClosestSol = (2 * 10 ** 6, 0) #Closest solution to 2 mil in the form (abs dif between rect count and 2 mil, area)
PrevRectCount = {(0): 0} #Previous rectangle counts in the form (x, y): rect count
TwoMil = 2 * 10 ** 6
x = 0 #x
y = 0 #y

#User def functions
def GetRectCount(x, y) -> int:
    Coords = (min(x, y), max(x, y))
    x = Coords[0]
    y = Coords[1]
    try:
        return PrevRectCount[Coords]
    except:
        if 0 in Coords:
            return 0
        temp = GetRectCount(x - 1, y) + GetRectCount(x, y - 1) - GetRectCount(x - 1, y - 1) + x * y
        PrevRectCount[(x, y)] = temp
        return temp

#Main
if __name__ == '__main__':
    while True:
        y += 1
        x = y - 1
        while True:
            x += 1
            print(x, y)
            temp = GetRectCount(x, y)
            if abs(temp - TwoMil) < ClosestSol[0]:
                ClosestSol = (abs(temp - TwoMil), x * y)
            if temp > TwoMil:
                break
        if x == y:
            break
    print(ClosestSol)
