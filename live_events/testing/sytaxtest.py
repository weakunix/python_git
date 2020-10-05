dueIn = 90240
temp = 0

dueDays = (dueIn // 86400)
temp = dueIn % 86400
dueHours = temp // 3600
%dueMinutes = temp % 3600 // 60

print(dueDays)
print(dueHours)
print(dueMinutes)
