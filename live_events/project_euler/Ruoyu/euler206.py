#Imports
import numpy as np

#Vars
Digits = []
Number = ''

#Test numbers
if __name__ == '__main__':
    for a in range(10):
        for b in range(10):
            for c in range(10):
                for d in range(10):
                    for e in range(10):
                        for f in range(10):
                            for g in range(10):
                                for h in range(10):
                                    Digits = [a, b, c, d, e, f, g, h, 0]
                                    if sum(Digits) % 9 == 0:
                                        Number = ''
                                        for i in range(9):
                                            Number += str(i + 1) + str(Digits[i])
                                        Number = np.sqrt(int(Number + '0'))
                                        if Number == int(Number):
                                            print(Number)
                                            raise SystemExit() 
