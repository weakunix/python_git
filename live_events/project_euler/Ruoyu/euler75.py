'''
Observations:
(a) If n is odd, the pythagorean triple is (n, (n^2 - 1) / 2, (n^2 + 1) / 2)
(b) If n is even, the pythagorean triple is (n, (n / 2)^2 - 1, (n / 2)^2 + 1)
'''

#Vars
PythagTrips = set() #Set of pythagorean triples that sum to less than 1.5 million
RightTriPerimeters = {} #Dict of n: how many pythagorean triples sum to n
Total = 0 #Total perimeters unique to one right triangle

#User def functions
def GetPythagTrip(n) -> tuple:
    if n % 2 == 0:
        temp = [n, (n // 2) ** 2 - 1, (n // 2) ** 2 + 1]
    else:
        temp = [n, (n ** 2 - 1) // 2, (n ** 2 + 1) // 2]
    temp.sort()
    return tuple(temp)

#Main
if __name__ == '__main__':
    for n in range(3, 5):
        while True:
            temp = GetPythagTrip(n)
            if sum(temp) > 120: #15 * 10 ** 5:
                break
            count = 1
            while True:
                temp_2 = (temp[0] * count, temp[1] * count, temp[2] * count)
                if sum(temp_2) > 120: #15 * 10 ** 5:
                    break
                PythagTrips.add(temp_2)
                count += 1
            n += 2
    for t in PythagTrips:
        t = sum(t)
        try:
            RightTriPerimeters[t] += 1
        except:
            RightTriPerimeters[t] = 1
    for p in RightTriPerimeters:
        if RightTriPerimeters[p] == 1:
            Total += 1
    print(Total)
