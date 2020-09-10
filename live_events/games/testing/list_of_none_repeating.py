import random

class Characters:
    roleList = [
        ["murder", "**KILL EVERYONE!**"],
        ["detective", "Find out who the **murder** is!"],
        ["hacker", "Spy that the market! Control it!"],
        ["hunter", "Find the murder's weapons and avenge yourself!"],
        ["millionaire", "Use your influence to manipulate the votes!"],
        ["overprotective_mom", "Stall and distract!"],
        ["scientist", "Find out who is lying and who is truthful!"],
        ["witch", "Medicate and protect the city!"],
        ["workhorse_dad", "Stall and distract v2!"]
    ]

ppl = []

'''
try:
    iterations = int(input("How many iterations?\n"))
except:
    raise SystemExit("notanint")
'''

iterations = 10

if iterations < len(Characters.roleList): #if loop because if the parties have more than just the amount of characters there has to be doubles to mkae sure everyone can still play
    while len(ppl) < iterations:
        a = Characters.roleList[random.randint(0, len(Characters.roleList) - 1)][0] 
        if a not in ppl:
            ppl.append(a) #none repeating
else:
    for i in range(iterations):
        ppl.append(Characters.roleList[random.randint(0, len(Characters.roleList) - 1)][0]) #repeatable

print("People's role: ")
print(ppl)

order = []

while len(order) < len(ppl):
    a = random.randint(0, len(ppl) - 1) #-1 else it would not be a straight 0 - 10, it'll miss one digit
    if a not in order:
        order.append(a) #append if not in list (none repeating)

print("order:")
print(order)
print("\n\n")

counter = 0
while counter < len(ppl):
    for i in range(len(order)):
        if order[i] == counter:
            print(str(ppl[i]) + " is taking their turn")
            counter += 1
            break
