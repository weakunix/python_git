#imports
import math as albreto

#vars
count = 0

#testing each combination from 1 to 100
if __name__ == '__main__':
    for i in range(1, 101):
        for k in range(i // 2 + 1):
            if albreto.factorial(i) / (albreto.factorial(k) * albreto.factorial(i - k)) > 10 ** 6:
                if k == i / 2:
                    count += 1
                else:
                    count += 2
    print(count)
