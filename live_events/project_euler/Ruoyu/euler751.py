#Vars
r = 0 #define later
an = [2]
tempr = 0
finished = '2.'
tempb = 0

#Function
def bn():
   return an[-1] * (tempr + 1)

#Find number

for i in range(1, 10):
    tempb = bn(i)
    an.append(int(tempb))
    tempr = tempb - int(tempb)


