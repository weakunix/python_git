#vars
digits = 1 #digits of the numbers we are testing
count = 0 #number of solutions


#testing each number from 0 to 9 as 10 ** n will always have n + 1 digits
for i in range(1, 10):
    digits = 1
    while len(str(i ** digits)) >= digits:
        if len(str(i ** digits)) == digits:
            count += 1
            print(i, digits)
        digits += 1
print(count)
