#Vars
t = 0

#Uesr def functions
def IsSNumber(DigitSource, TargetNum):
    DigitSource = str(DigitSource)
    for i in range(1, 2 ** (len(DigitSource) - 1)):
        Digits = DigitSource
        DigitSum = 0
        DigitAmount = 0
        IsFirstTime = True
        #import pdb;pdb.set_trace()
        while i > 0:
            DigitAmount += 1
            if i % 2:
                DigitSum += int(Digits[:DigitAmount])
                Digits = Digits[DigitAmount:]
                DigitAmount = 0
            if IsFirstTime and DigitSum > TargetNum:
                break
            IsFirstGame = False
            i >>= 1
        DigitSum += int(Digits)
        if DigitSum == TargetNum:
            return True
    return False

#Test for s numbers
if __name__ == '__main__':
    for i in range(1, 10 ** 6 + 1):
        if i % 1000 == 0:
            print(i)
        if IsSNumber(i ** 2, i):
            t += i ** 2
    
    print(t)
