'''
Observations:
(a) How I solve normal Sudoku puzzles: mark each empty cell with possible numbers
If only one number exists, that is the only number that will work in that cell
Place it in
If there exists no cell with only one number, try guessing a cell with its possible values
Assuming those numbers are correct, one of them will work
(b) In this, be mindful that the elimination of impossible numbers do not exist, like in the Sudoku games where a cell with [1, 2, 3] possible will become [1, 2] when 3 is placed in the same row
(c) We are going to solve the entire Sudoku puzzle to ensure that a solution works, however we just have to return the 3 digit number in the top left grid

Approach:
Using Observation (a) make a Sudoku class that contains methods for finding possible cell numbers and placing numbers in
Remember to break after one number is placed and to be sure to reload the columns and 3x3 mini grids whenever a number is placed as to avoid an Observation (b) logical bug
Whenever there exists no cell with only one number, use the method in Observation (a) and create an instance of class Sudoku with one cell being guessed
This is recursive since it will then try to solve the new grid
A grid with no solution will return -1
This recursive function will solve the entire grid as to meet the conditions in Observation (c)
'''

#Vars
Puzzles = [] #List of all Sudoku puzzles
Total = 0 #Sum of all 3 digit nums of all Sudoku puzzles

#Classes
class Sudoku:
    
    def GenColumns(self, Rows) -> list:
        return [[r[i] for r in Rows] for i in range(9)]

    def GenGrids(self, Columns) -> list:
        Grids = [[] for i in range(9)]
        for y in range(9):
            for x in range(9):
                Grids[x // 3 + y // 3 * 3].append(Columns[x][y])
        return Grids

    #INIT
    def __init__(self, Puzzle) -> None:
        self.Rows = Puzzle
        self.Columns = self.GenColumns(self.Rows)
        self.Grids = self.GenGrids(self.Columns)

    def Solve(self) -> int: #3 digit num if success, -1 if fail
        while True:
            Unsolved = {(x, y): self.FindPossibleVals(x, y) for y in range(9) for x in range(9) if self.Rows[y][x] == 0}
            if len(Unsolved) == 0:
                return int(str(self.Rows[0][0]) + str(self.Rows[0][1]) + str(self.Rows[0][2]))
            if [] in Unsolved.values():
                return -1
            UniqueValFound = False
            for i in Unsolved:
                x = i[0]
                y = i[1]
                if len(Unsolved[i]) == 1:
                    self.Rows[y][x] = Unsolved[i][0]
                    self.Columns = self.GenColumns(self.Rows)
                    self.Grids = self.GenGrids(self.Columns)
                    UniqueValFound = True
                    break
            if not UniqueValFound:
                break
        temp = list(Unsolved.keys())[0]
        for i in Unsolved[temp]:
            SubPuzzle = []
            for r in self.Rows:
                SubPuzzle.append(r.copy())
            SubPuzzle[temp[1]][temp[0]] = i
            SubPuzzle = Sudoku(SubPuzzle).Solve()
            if SubPuzzle > 0:
                return SubPuzzle
        return -1

    def FindPossibleVals(self, x, y) -> list:
        RemainingVals = {i for i in range(1, 10)}
        ValsUnavail = set(self.Rows[y] + self.Columns[x] + self.Grids[x // 3 + y // 3 * 3])
        return list(RemainingVals - ValsUnavail)

#Read file
with open('p096_sudoku.txt', 'r') as f:
    temp = []
    for line in f:
        line = line.strip('\n')
        if 'Grid' in line:
            if temp != []:
                Puzzles.append(Sudoku(temp))
                temp = []
        else:
            temp.append([int(i) for i in line])
    Puzzles.append(Sudoku(temp))

#Main
if __name__ == '__main__':
    for i in Puzzles:
        Total += i.Solve()
    print(Total)
