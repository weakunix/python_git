'''
Observations:
(a) A number is either increasing, decreasing, or bouncy
(b) A number that is increasing or decreasing that has n digits can be used to generate new increasing/decreasing numbers with n + 1 digits by appending digits to the end of the number
Let d be the last digit of that number
If that number is increasing, we can add the digits d to 9
If that number is decreasing, we can add the digits 0 to d

Approach:
We can use Observation (b) to generate sets of increasing and decreasing numbers efficiently
Loop through numbers with 1, 2, 3, ... digits and add to the count of bouncy numbers if the number cannot be found in the increasing or decreasing number sets
For each number, check if the bouncy number count / the number we are testing == 0.99
Terminate the program if the condition above is true
'''

#Vars
BouncyNumCount = 0 #Bouncy number count
IncreasingNums = {i for i in range(1, 10)} #Set of increasing numbers
DecreasingNums = IncreasingNums #Set of decreasing numbers
DigitCount = 1 #Digit count of testing numbers

#User def functions
def GenNewSets() -> None:
    global IncreasingNums, DecreasingNums
    NewSet = set()
    for i in IncreasingNums:
        i = str(i)
        for d in range(int(i[-1]), 10):
            NewSet.add(int(i + str(d)))
    IncreasingNums = NewSet
    NewSet = set()
    for i in DecreasingNums:
        i = str(i)
        for d in range(0, int(i[-1]) + 1):
            NewSet.add(int(i + str(d)))
    DecreasingNums = NewSet

#Main
while True:
    DigitCount += 1
    GenNewSets()
    for i in range(10 ** (DigitCount - 1), 10 ** DigitCount):
        if i not in IncreasingNums and i not in DecreasingNums:
            BouncyNumCount += 1
        if BouncyNumCount / i == 0.99:
            print(i)
            raise SystemExit()
