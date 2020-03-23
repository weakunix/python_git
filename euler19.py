'''
Euler 19
COUNTER TO COUNT ALL SUNDAYS:
    1. Check dow. If dow is 0 (Sunday) add one to count
    2. Add days to dow with dictionary dim
    3. Check leap year
    4. Add 1 to year 
'''

#vars
year = 1900
dow = 1
count = 0
leap = False

#dictionaries
dim = { 1: 31,
        2: 28,
        3: 31,
        4: 30,
        5: 31,
        6: 30,
        7: 31,
        8: 31,
        9: 30,
        10: 31,
        11: 30,
        12: 31  }

#user def functions
def leap_check(year):
    if year % 4 == 0 and year % 100 != 0 or year % 400 == 0:
        return True
    else:
        return False


#counter to find sundays
while year != 2001:
    leap = leap_check(year)
    for i in range(1, 13):
        dow %= 7
        if year != 1900 and dow == 0:
            count += 1
        dow += dim[i]
        if i == 2 and leap == True:
            dow += 1
    year += 1
print(count) 
