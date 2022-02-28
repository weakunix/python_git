'''
Observations:
(a) Only have to test the biggest n / d that is less than 3 / 7

Approach:
Use Observation a and just test it
'''

#Vars
ClosestN = (None, None) #Value of n for which 3 / 7 - n / d is minimized in the form of (3 / 7 - n / d, n)

#Main
if __name__ == '__main__':
    for d in range(1, 10 ** 6 + 1):
        n = (3 * d - 1) // 7
        try:
            if 3 / 7 - n / d < ClosestN[0]:
                ClosestN = (3 / 7 - n / d, n)
        except:
            ClosestN = (3 / 7 - n / d, n)
    print(ClosestN)
