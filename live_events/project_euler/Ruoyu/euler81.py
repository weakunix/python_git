'''
Observations:
(a) We can map every point in the matrix to (x, y) where (0, 0) is the top left element
(b) We can work backwards from (79, 79) to (78, 79) to (77, 79) ... (79, 78), (78, 78) ... (0, 0)
(c) For each point, we can find the minimum of (x + 1, y) and (x, y + 1), with exceptions when x or y = 79, and add the value of the current point
This way, we will find the minimum sum of (0, 0)

Approach:
Read the file and map each point in the way stated in Observation (a)
We then work backwards (Observation (b)) and use Observation (c) to calculate each succeeding point's minimum sum
We will eventually reach (0, 0) and return that value
'''

#Vars
Points = [] #List of points (x, y)
PointsDict = {} #Dict of points and their values
MinPathsDict = {} #Dict of points and their minimum path sum

#Read file
with open('p081_matrix.txt', 'r') as f:
    for y, line in enumerate(f):
        line.strip('\n')
        line = line.split(',')
        for x, val in enumerate(line):
            Points.append((x, y))
            PointsDict[(x, y)] = int(val)

#Main
if __name__ == '__main__':
    Points.reverse()
    for i in Points:
        x = i[0]
        y = i[1]
        if x < 79 and y < 79:
            MinPathsDict[i] = min(MinPathsDict[(x + 1, y)], MinPathsDict[(x, y + 1)]) + PointsDict[i]
        elif x < 79:
            MinPathsDict[i] = MinPathsDict[(x + 1, y)] + PointsDict[i]
        elif y < 79:
            MinPathsDict[i] = MinPathsDict[(x, y + 1)] + PointsDict[i]
        else:
            MinPathsDict[i] = PointsDict[i]
    print(MinPathsDict[(0, 0)])
