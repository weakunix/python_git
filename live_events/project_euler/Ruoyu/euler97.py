#Vars
Num = 1

#Powers of two
for i in range(7830457):
    Num = int(str(Num * 2)[-10:])

#Rest of the expression
print(int(str(Num * 28433)[-10:]) + 1)
