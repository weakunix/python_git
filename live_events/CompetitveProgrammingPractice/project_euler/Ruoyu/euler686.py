#Imports
import numpy as np

#Vars
CurrentPow = 0
PowerVal = 0
Total = 0
MinCorrectVal = np.log10(1.23)
MaxCorrectVal = np.log10(1.24)

#Test numbers
while Total < 678910:
    CurrentPow += 1
    PowerVal = np.log10(2) * CurrentPow - int(np.log10(2) * CurrentPow)
    if PowerVal >= MinCorrectVal and PowerVal < MaxCorrectVal:
        Total += 1
        if Total % 100 == 0:
            print(Total)

print(CurrentPow)
