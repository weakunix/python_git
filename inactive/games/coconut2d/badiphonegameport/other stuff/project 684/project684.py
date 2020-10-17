import random

h = open("example.txt", "w");
leng = int(input("length and width (1 number)\n"))  # length and width
gameArray = [[random.randint(0, 3) for x in range(0, leng)] for y in range(0, leng)]
print(gameArray)
h.write(str(gameArray))
h.close()


# to read
def check(gameArray, x, y):
    print(x, y, gameArray[x][y])
    if x != leng-1 or y != leng-1 or x != 0 or y != 0:
        if gameArray[x][y] == gameArray[x + 1][y] and gameArray[x][y] == gameArray[x - 1][y]:
            print("h")
        if gameArray[x][y] == gameArray[x][y + 1] and gameArray[x][y] == gameArray[x][y - 1]:
            print("v")


for i in range(len(gameArray) - 1):
    for ii in range(len(gameArray[i]) - 1):
        check(gameArray, i, ii)
