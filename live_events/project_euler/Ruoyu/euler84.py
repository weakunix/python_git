'''
Observations:
(a) We can simulate a ton of dice rolls and find the three most visited squares

Approach:
BFI using Observation (a)
'''

#Imports
import random as rand

#Vars
Moves = 10 ** 6 #Constant moves for simulation but should be tweaked if inconsistent results are shown
Dice = 4 #Dice faces
CurSqr = 0 #Current square
Visits = [0 for _ in range(40)] #Visits per square
DoubleCount = 0 #Number of doubles in a row
ComChest = [-1 for _ in range(14)] + [0, 10] #Community chest (-1 is nothing)
Chance = [-1 for _ in range(6)] + [0, 10, 11, 24, 39, 5, -2, -2, -3, -4] #Chance (-1 is nothing, -2 is next railroad, -3 is back three steps, -4 is next utility)
ThreeMost =  {i: i for i in range(-3, 0)} #Dict of visits : square num (for three most visits)

#Set vars
rand.shuffle(ComChest)
rand.shuffle(Chance)

#Main
if __name__ == '__main__':
    for i in range(Moves):
        a = rand.randint(1, Dice)
        b = rand.randint(1, Dice)
        if a == b:
            DoubleCount += 1
        else:
            DoubleCount = 0
        CurSqr = (CurSqr + a + b) % 40
        if DoubleCount == 3:
            DoubleCount = 0
            CurSqr = 10
        elif CurSqr == 30:
            CurSqr = 10
        elif CurSqr in [2, 17, 33]:
            temp = ComChest.pop(0)
            if temp >= 0:
                CurSqr = temp
            ComChest.append(temp)
        elif CurSqr in [7, 22, 36]:
            temp = Chance.pop(0)
            if temp >= 0:
                CurSqr = temp
            elif temp == -2:
                if CurSqr == 7:
                    CurSqr = 15
                elif CurSqr == 22:
                    CurSqr = 25
                else:
                    CurSqr = 5
            elif temp == -3:
                CurSqr -= 3
            elif temp == -4:
                if CurSqr == 22:
                    CurSqr = 28
                else:
                    CurSqr = 12
            Chance.append(temp)
        Visits[CurSqr] += 1
    for s, v in enumerate(Visits):
        if v in Visits:
            v -= 1
        if min(ThreeMost) < v:
            ThreeMost.pop(min(ThreeMost))
            ThreeMost[v] = s
    print(Visits, ThreeMost)
