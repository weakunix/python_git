'''
Observations:
(a) We can map every point in the matrix to (x, y) where (0, 0) is the top left element
(b) We can work backwards from (79, 79) to (79, 78) to (79, 77) ... (78, 79), (78, 78) ... (0, 0)
(c) For each point, we can find the best possible paths going only up, down, and right (down and right are just one test each with (x + 1, y) and (x, y + 1) while up is testing all possible (x, y - n) for n <= y
(d) Once minimum up, down, and right paths have been found for each point, we can keep looping the following process:
Loop through every point and recalibrate its minimum up, down, and right path
Then test if moving left is more effective
If so, use the left path
Else, use the recalibrated up, down, and right path
(e) Continuously looping the above will eventually result in the most effective up, down, left, and right path

Approach:
Read the file and map each point in the way stated in Observation (a)
We then work backwards (Observation (b)) and use Observation (c) to calculate each succeeding point's minimum sum
Then use Observations (d) and (e) to get the minimum up, down, left, and right path sum
Return the value at (0, 0)
'''

#Vars
Points = [(x, y) for x in range(80) for y in range(80)] #List of points (x, y)
PointsDict = {} #Dict of points and their values
MinPathsDict = {} #Dict of points and their minimum path sum
UpdatedDict = {} #Updated MinPathsDict with recalibrated path sums and left direction checks

#User def functions
def GetMinPathSum(x, y, d) -> int:
        if x < 79 and y < 79:
            temp = min(d[(x + 1, y)], d[(x, y + 1)]) + PointsDict[i]
        elif x < 79:
            temp = d[(x + 1, y)] + PointsDict[i]
        elif y < 79:
            temp = d[(x, y + 1)] + PointsDict[i]
        else:
            temp = PointsDict[i]
        if x != 79:
            count = PointsDict[i]
            while y != 0:
                y -= 1
                count += PointsDict[(x, y)]
                if count + d[(x + 1, y)] < temp:
                    temp = count + d[(x + 1, y)]
        return temp

#Read file
with open('p083_matrix.txt', 'r') as f:
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
        MinPathsDict[i] = GetMinPathSum(x, y, MinPathsDict)
    UpdatedDict = MinPathsDict.copy()
    while True:
        for i in Points:
            x = i[0]
            y = i[1]
            temp = GetMinPathSum(x, y, UpdatedDict)
            if x > 0:
                if UpdatedDict[(x - 1, y)] + PointsDict[i] < temp:
                    temp = UpdatedDict[(x - 1, y)] + PointsDict[i]
            UpdatedDict[i] = temp
        if MinPathsDict == UpdatedDict:
            break
        MinPathsDict = UpdatedDict.copy()
    print(MinPathsDict[(0, 0)])
