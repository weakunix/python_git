#Imports
import numpy as np

#Vars
MinNum = int(np.sqrt(1020304050607080900))
MaxNum = int(np.sqrt(1929394959697989900)) + 1

#User def functions
##Does square of a number meet criteria
def IsCorrectSquare(x):
    x = str(x ** 2)
    for i in range(0, len(x), 2):
        if str((int(i / 2) + 1) % 10) != x[i]:
            return False
    return True

#Test numbers
if __name__ == '__main__':
    print(MinNum, MaxNum)
    for i in range(MinNum, MaxNum, 10): #MinNum happens to be divisible by 10
        if i % 1000000 == 0:
            print(i)
        if IsCorrectSquare(i):
            print(i)
            raise SystemExit()
