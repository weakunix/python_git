#import
import albretotools as at

#vars
length = 1 #square side length
total = 1 #total numbers in diagonals
prime = 0 #total primes in diagoonals
num = 1 #current num

#adding layers to the square until primes in diagonals / total in diagonals < 10%
while prime / total >= 0.1 or length == 1:
    length += 2
    total += 4
    for i in range(4):
        num +=  length - 1
        if at.is_prime(num):
            prime += 1
print(length)
