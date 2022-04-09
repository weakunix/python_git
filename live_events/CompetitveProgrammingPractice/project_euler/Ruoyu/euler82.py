'''
Observations:
(a) We can map every point in the matrix to (x, y) where (0, 0) is the top left element
(b) We can work backwards from column x = 79 to column x = 78 ... column x = 1 to column x = 0
(c) For each point in a column, test possible path sums to the next column by moving up and down
The minimum of the set of path sums to the next column is assigned to the point

Approach:
Read the file and map each point in the way stated in Observation (a)
We then work backwards by columns (Observation (b)) and use Observation (c) to calculate each succeeding column's points' minimum sum
We will eventually reach the column x = 0 and find the minimim path sum point
'''

#Vars
Points = [(x, y) for x in range(80) for y in range(80)] #List of points (x, y)
PointsDict = {} #Dict of points and their values
MinPathsDict = {} #Dict of points and their minimum path sum
PossiblePaths = set() #Set of possible path sums for a point
MinPathSum = 0 #Minimum path sum

#Read file
with open('p082_matrix.txt', 'r') as f:
    for y, line in enumerate(f):
        line.strip('\n')
        line = line.split(',')
        for x, val in enumerate(line):
            PointsDict[(x, y)] = int(val)

#Main
if __name__ == '__main__':
    Points.reverse()
    for i in Points:
        x = i[0]
        y = i[1]
        if x == 79:
            MinPathsDict[i] = PointsDict[i]
        else:
            mtv = PointsDict[i] + MinPathsDict[(x + 1, y)]
            OriginalY = y
            PossiblePaths = {mtv}
            temp = PointsDict[i]
            while temp < mtv and y != 79:
                y += 1
                temp += PointsDict[(x, y)]
                PossiblePaths.add(temp + MinPathsDict[(x + 1, y)])
            temp = PointsDict[i]
            y = OriginalY
            while temp < mtv and y != 0:
                y -= 1
                temp += PointsDict[(x, y)]
                PossiblePaths.add(temp + MinPathsDict[(x + 1, y)])
            MinPathsDict[i] = min(PossiblePaths)
    MinPathSum = MinPathsDict[(0, 0)]
    for y in range(80):
        if MinPathsDict[(0, y)] < MinPathSum:
            MinPathSum = MinPathsDict[(0, y)]
    print(MinPathSum)
