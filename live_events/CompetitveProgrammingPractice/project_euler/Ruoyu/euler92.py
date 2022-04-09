#vars
LeadTo89 = {89}
LeadTo1 = {1}
TotalLeadTo89 = 0
Count = 0

#functions
##sum of squares of digits
def SumDigitSquares(n):
    SumSquares = 0
    while n > 0:
        SumSquares += (n % 10) ** 2
        n = int(n / 10)
    return SumSquares

##make number
def MakeNumber(a, b, c, d, e, f, g):
    n = 0
    Multiply = 1
    for i in [g, f, e, d, c, b, a]:
        n += i * Multiply
        Multiply *= 10
    return n

#trying all numbers
for a in range(10):
    for b in range(10):
        for c in range(10):
            for d in range(10):
                for e in range(10):
                    for f in range(10):
                        for g in range(10):
                            if Count != 0:
                                if Count % 1000 == 0:
                                    print(Count)
                                DigitSum = sum([i ** 2 for i in [a, b, c, d, e, f, g]])
                                if DigitSum in LeadTo89:
                                    if Count <= 9 ** 2 * 7:
                                        LeadTo89.add(Count)
                                    TotalLeadTo89 += 1
                                elif DigitSum in LeadTo1:
                                    if Count <= 9 ** 2 * 7:
                                        LeadTo1.add(Count)
                                else:
                                    if Count > 9 ** 2 * 7:
                                        raise SystemExit('BUG')
                                    while True:
                                        DigitSum = SumDigitSquares(DigitSum)
                                        if DigitSum in LeadTo89:
                                            LeadTo89.add(Count)
                                            TotalLeadTo89 += 1
                                            break
                                        elif DigitSum in LeadTo1:
                                            LeadTo1.add(Count)
                                            break
                            Count += 1
print(TotalLeadTo89)