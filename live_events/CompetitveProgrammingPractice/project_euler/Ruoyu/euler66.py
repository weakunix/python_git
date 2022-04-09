'''
Observations:
x^2 - 1 = Dy^2
(x + 1)(x - 1) = Dy^2

Approach:
Chakravala method (google for reminder)
'''

#Vars
DForMax = (None, None) #Value of D for maximum x in the form of (x, D)
Squares = {i ** 2 for i in range(1, 32)}

#User def functions
def GetMinM(trip, D) -> int:
    m = 0
    x = trip[0]
    y = trip[1]
    k = trip[2]
    #k | x + ym
    while True:
        m += 1
        if (x + y * m) % k == 0 and m ** 2 > D:
            return m

def ComposeTriples(a, b, D) -> tuple:
    x = a[0]
    y = a[1]
    k = a[2]
    m = b[0]
    k2 = b[2]
    NewX = (x * m + y * D) // k
    NewY = (x + y * m) // k
    NewK = k2 // k
    return (NewX, NewY, NewK)

#Main
if __name__ == '__main__':
    for D in range(1, 1001):
        if D not in Squares:
            print(D)
            x = 0
            while x ** 2 < D:
                x += 1
            y = 1
            k = x ** 2 - D
            temp = (x, y, k)
            while temp[2] != 1:
                m = GetMinM(temp, D)
                temp = ComposeTriples(temp, (m, 1, m ** 2 - D), D)
            try:
                if temp[0] > DForMax[0]:
                    DForMax = (temp[0], D)
            except:
                DForMax = (temp[0], D)
    print(DForMax)
