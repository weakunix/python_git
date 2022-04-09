#vars
sumn = 0
digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
d1 = 0
d2 = 0
d3 = 0
d4 = 0
d5 = 0
d6 = 0
d7 = 0
d8 = 0
d9 = 0
d10 = 0

#user def functions
#check is number has sub-string divisibility property
def has_substring_property(num):
    nums = [2, 3, 5, 7, 11, 13, 17]
    num = str(num)
    for i in range(1, 8):
        if int(num[i:i + 3]) % nums[i - 1] != 0:
            return False
    return True

#trying all 0 to 9 pandigital numbers and looking for sub-string divisibility property
for a in range(1, 10):
    for b in range(9):
        for c in range(8):
            for d in range(7):
                for e in range(6):
                    for f in range(5):
                        for g in range(4):
                            for h in range(3):
                                for i in range(2):
                                    digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
                                    d1 = str(digits.pop(a))
                                    d2 = str(digits.pop(b))
                                    d3 = str(digits.pop(c))
                                    d4 = str(digits.pop(d))
                                    d5 = str(digits.pop(e))
                                    d6 = str(digits.pop(f))
                                    d7 = str(digits.pop(g))
                                    d8 = str(digits.pop(h))
                                    d9 = str(digits.pop(i))
                                    d10 = str(digits[0])
                                    d1 = int(d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9 + d10)
                                    print(d1)
                                    if has_substring_property(d1):
                                        sumn += d1
print(sumn)
