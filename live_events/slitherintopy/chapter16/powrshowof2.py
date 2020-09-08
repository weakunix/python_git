'''
Problem:
Write a recursive function that takes an integer as an argument and returns whether or not that integer is a power of 2. Your function should return True or False
'''

def checkifpowerof2(check, num = None) -> bool:
    if num == None:
        num = 1
    if 2 ** num == check:
        print(True)
        return True
    elif 2 ** num > check: #if squared is over the number then its not it
        print(False)
        return False
    checkifpowerof2(check, num + 1)

checkifpowerof2(16) #returns true because it is a power of 2!!!!