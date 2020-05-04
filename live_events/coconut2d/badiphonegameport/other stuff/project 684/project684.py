import random

leng = int(input("length and width (1 number)\n"))  # length and width
gameArray = [[random.randint(0, 3) for x in range(0, leng)] for y in range(0, leng)]
print(gameArray)
# to read
for i in range(len(gameArray)):
    for ii in range(len(gameArray[i])):
        print(gameArray[i][ii])
