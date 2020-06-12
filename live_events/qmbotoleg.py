print("Qmbo To Legendary Calculator! V1.1")
import math as albreto
points = int(input("How many points u at rn"))
daysLeft = int(input("How many days left?"))
sessionsPerDay = int(input("How many sessions per day?"))
avgPointPerRound = 30
legPoints = 6501
pointsNeeded = legPoints - points
pointsperday = (pointsNeeded/daysLeft)
pointspersession = pointsperday/sessionsPerDay
rounds = albreto.ceil(pointspersession/avgPointPerRound)
print("================== cowculating ==================== \n"+" Points Needed: \n"+str(pointsNeeded)+"\n Points Per Day (rounded up): \n"+str(albreto.ceil(pointsperday))+"("+str(pointsperday)+")"+"\n Points Per Session (rounded up): \n"+str(albreto.ceil(pointspersession))+"("+str(pointspersession)+")"+"\n You need to win "+str(rounds)+" rounds per session! Get to grinding!")
