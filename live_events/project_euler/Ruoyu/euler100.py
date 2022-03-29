
#Imports
import math as albreto

#Vars
n = 1 #n

#Main
if __name__ == '__main__':
    while True:
        n += 1
        temp = (n * (n - 1)) // 2
        count = int(albreto.sqrt(temp))
        while True:
            temptemp = count * (count + 1)
            if temptemp > temp:
                break
            if temptemp == temp:
                print(n, count + 1, n - count - 1, (count + 1) / (n - count - 1))
            count += 1
