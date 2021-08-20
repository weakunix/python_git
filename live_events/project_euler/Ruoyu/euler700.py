#Vars
CurrentVal = 1504170715041707
NewVal = 0
ConstantVal = CurrentVal
ModNum = 4503599627370517
CurrentCoin = ConstantVal
CoinSum = ConstantVal
CoinDif = ConstantVal + 1

while CurrentCoin > 0:
    if CurrentCoin >= CoinDif:
        CurrentCoin -= CoinDif
        CoinSum += CurrentCoin
        CurrentVal = CurrentCoin
        print(CurrentCoin)
    else:
        NewVal = ConstantVal - (ModNum - CurrentVal) % ConstantVal
        if NewVal < CurrentCoin:
            CurrentVal = NewVal
            CoinDif = CurrentCoin - CurrentVal
            CurrentCoin = CurrentVal
            CoinSum += CurrentCoin
            print(CurrentCoin)
        else:
            CurrentVal = NewVal

print(CoinSum)
