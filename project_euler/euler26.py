#vars
digits = 0
longest = 0

#user def functions
def find_recurring(d):
    digits = 1
    while digits % d != 0:
        if digits == 1:
            digits = 0
        digits = int(str(digits) + '9')
    return len(str(digits))


#find longest recurring cycle
for i in range(2, 1000):
    if i % 2 !=  0 and i % 5 != 0:  
        digits = find_recurring(i)
        if digits > longest:
            longest = i
print(longest)
