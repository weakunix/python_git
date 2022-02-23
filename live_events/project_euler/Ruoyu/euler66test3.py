'''
Observations:
x^2 - 1 = Dy^2
(x + 1)(x - 1) = Dy^2

Shift x by -1
(x - 2)x = Dy^2
Result is the same

Possibilities:
Try BFI through all D <= 1000 and find minimal solutions

Or

Instead of looping through D, we loop through x until there is only one D left between 1 to 100
For every x >= 2, we check every y^2 in the following range and find every (x^2 - 1) / y^2
If that is an integer, we remove that D from the list
Optimization: instead of checking every y^2, run some sort of prime factorization algorithm to figure out which y^2 will work

Or

Use the observation above that states (x - 2)x = Dy^2
Loop through x and store values up until x - 2 (on each iteration we can pop x - 3 value)

x = p * q^2 where p is not square
x - 2 = r * s^2 (which has already been stored)

(x - 2)x = p * r * (q * s)^2
'''

#Imports
import math as albreto

#Vars
x = 0 #x - 1
XStorage = [] #Factored x = p * q^2 form storage up until x - 2
TestVal = 1001 #Testing value (should be 1001)
DVals = set(i for i in range(1, TestVal) if not albreto.sqrt(i).is_integer())

#User def functions
def GetFactorsOfTwo(n) -> int:
    count = 0
    while True:
        if n % 2 == 0:
            n /= 2
            count += 1
        else:
            return count

def GetXForm(x) -> tuple:
    HasExtraTwo = GetFactorsOfTwo(x) % 2 == 1
    if HasExtraTwo:
        x //= 2
    for i in range(1, TestVal):
        if (x / i).is_integer():
            temp = albreto.sqrt(x / i)
            if temp.is_integer():
                return (i, int(temp), HasExtraTwo)
    return None

def XFormMultiply(a, b) -> tuple:
    D = a[0] * b[0]
    y = a[1] * b[1]
    temp = a[2] + b[2]
    if temp == 0:
        return (D, y)
    if temp == 1:
        return (D * 2, y)
    return (D, y * 2)
    

#Main
if __name__ == '__main__':
    while True:
        x += 1
        #print(len(DVals), x)
        XStorage.append(GetXForm(x))
        try:
            XStorage.pop(-4)
        except:
            pass
        try:
            temp = XFormMultiply(XStorage[0], XStorage[2])
            D = temp[0]
            y = temp[1]
            count = 0
            while True:
                count += 1
                if count ** 2 * D > 1000 or count > y:
                    break
                if y % count == 0:
                    try:
                        DVals.remove(D * count ** 2)
                        print(x, D * count ** 2, y, len(DVals))
                    except:
                        pass
        except:
            pass
        if len(DVals) == 1:
            break
    print(list(DVals)[0])
