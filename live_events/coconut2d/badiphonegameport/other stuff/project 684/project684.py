import random
len = int(input("length and width (1 number)\n")) #length and width
gameArray = [[random.randint(0, 3) for x in range(0, len)]for y in range(0, len)]
print(gameArray)
