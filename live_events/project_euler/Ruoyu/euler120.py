'''
Observations:
(a) (a - 1) ^ n + (a + 1) ^ n % a ^ 2 = 2 when n is even and 2an when n is odd

Approach:
Loop from 3 to 1000 and use Observation (a)
Keep a count and add 2a twice (so n remains odd) until a remaninder repeats
Get the max remainder and add it to the sum
'''

#Vars
MaxRSum = 0 #Sum of all max r
Remainders = set() #Set of remainders

#Main
if __name__ == '__main__':
    for a in range(3, 1001):
        Remainders = set()
        temp = 2 * a
        while temp not in Remainders:
            Remainders.add(temp)
            temp = (temp + 4 * a) % a ** 2
        MaxRSum += max(Remainders)
    print(MaxRSum)
