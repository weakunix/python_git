'''
Test outputs:

1:
90

CORRECT PROGRAM!

Theory:

Think of visits like a directed graph
We can have connected section (1 -> 2 -> 3 -> 1) in which case we can add sum(Moos) - min(Moos)
There are also loose ends that can come off of each of the connected section nodes
We can find these by looping through all nodes and finding whichever ones have no inward connections
Remove those nodes and loop until there are no changes
Then calculate connected sections
'''

#Vars
N = int(input())
Visits = {}
Moos = {}
Groups = set()
TotalMoos = 0
MinMoo = 0

for i in range(1, N + 1):
    temp = input().split()
    Visits[i] = int(temp[0])
    Moos[i] = int(temp[1])

#Unconnected visits
Prev = 0
while Prev != len(Visits):
    Prev = len(Visits)
    NonConnected = set()
    temp = set(Visits.values())
    for i in Visits:
        if i not in temp:
            TotalMoos += Moos[i]
            NonConnected.add(i)
    for i in NonConnected:
        Visits.pop(i)

#Connected visits
while len(Visits) > 0:
    count = list(Visits.keys())[0]
    NewGroup = set()
    while True:
        NewGroup.add(count)
        try:
            temp = Visits[count]
            Visits.pop(count)
            count = temp
        except:
            break
    Groups.add(tuple(NewGroup))

for i in Groups:
    MinMoo = None
    for k in i:
        temp = Moos[k]
        try:
            if MinMoo > temp:
                TotalMoos += MinMoo
                MinMoo = temp
            else:
                TotalMoos += temp
        except:
            MinMoo = temp

print(TotalMoos)
