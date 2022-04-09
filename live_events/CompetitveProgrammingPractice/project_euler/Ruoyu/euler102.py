'''
Observations:
(a) A triangle can intersect the y axis 0, 1, or 2 times
For the sake of simplicity, we shall group the case of 1 and 2 intersections together and say that the case of 1 intersection is intersecting twice on the same point
(b) If a triangle intersects the y axis 0 times, the origin will not be contained in the triangle
This can be detected when all x coordinates are positive
(c) In the case of 2 (and 1) intersections, we can use slope to find the two y intercepts of the triangle
(d) When 0 is in the range of the two y intercepts, the triangle contains the origin

Approach:
Test each triangle using Observations (b), (c), and (d)
'''

#Vars
CoordList = [] #List of coordinates
Count = 0 #Number of triangles that contain the origin
YInts = [] #The y intercepts of the triangles

#User def functions
def GetYInt(a, b) -> float:
    try: 
        if a[0] / b[0] > 0:
            return None
    except: #exception when x of a is 0
        pass
    try:
        k = (b[1] - a[1]) / (b[0] - a[0])
    except: #exception when slope is undefined (vertical line)
        return None
    return a[1] - a[0] * k

#Read file
with open('p102_triangles.txt', 'r') as f:
    for line in f:
        tri = []
        coord = []
        for i in line.split(','):
            coord.append(int(i))
            if len(coord) == 2:
                tri.append(tuple(coord))
                coord = []
        CoordList.append(tri)

#Main
if __name__ == '__main__':
    for tri in CoordList:
        a = tri[0]
        b = tri[1]
        c = tri[2]
        YInts = [GetYInt(a, b), GetYInt(b, c), GetYInt(a, c)]
        if YInts.count(None) == 1:
            YInts.pop(YInts.index(None))
            try:
                if YInts[0] / YInts[1] <= 0:
                    Count += 1
            except: #exception when dividing y intercept is 0
                Count += 1
    print(Count)
