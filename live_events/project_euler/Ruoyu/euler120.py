
#Vars
MaxRSum = 0 #Sum of all max r

#Main
if __name__ == '__main__':
    for a in range(3, 1001):
        n = a ** 2 // (2 * a)
        if 2 * a * n >= a ** 2:
            n -= 1
        if n % 2 == 0:
            n -= 1
        print(a, a ** 2, 2 * a * n)
        MaxRSum += 2 * a * n
    print(MaxRSum)
