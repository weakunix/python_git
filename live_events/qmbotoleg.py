import math as albreto
points = int(input("How many points u at rn"))
daysLeft = int(input("How many days left?"))
sessionsPerDay = int(input("How many sessions per day?"))
legPoints = 6501
pointsNeeded = legPoints - points
print("Points Needed: \n"+str(pointsNeeded)+"\n ================== cowculating ==================== \n")
pointsperday = (pointsNeeded/daysLeft)
print("points per day: \n"+str(pointsperday))
pointspersession = pointsperday/sessionsPerDay
print("points per session: \n"+str(pointspersession))
