import random as randomino
import tkinter as tk
from PIL import Image, ImageTk
from functools import partial

window = tk.Tk()
window.title("raaa generator pls wrk")
window.configure(bg="cyan")  # background of the window
window.geometry("840x630")
imagesforgame = []
usedcenters = [[]]
seed = [[0 for y in range(30)] for x in range(40)]
rendershit = False
arraytodel = [[0 for y in range(30)] for x in range(40)]
bsize = 0
xloc = 0
yloc = 0


def main():
    global seed
    global rendershit
    global arraytodel
    global imagesforgame
    imageload(20)
    for y in range(0, 30):
        for x in range(0, 40):
            a = randomino.randint(0, 10)  # generates all grass
            if a == 10:
                seed[x][y] = 3
            else:
                seed[x][y] = 1

    for y in range(0, 30):  # smort generation ocean
        seed[37][y] = 13
        seed[38][y] = 14
        seed[39][y] = 16

    for i in range(randomino.randint(1, 3)):
        seed[38][randomino.randint(0, 29)] = 15  # 1-3 docks every game

    for y in range(0, 30):
        temp = []
        for x in range(0, 40):
            temp.append(seed[x][y])

    spawnTerrain("grassmtn")
    for i in range(2):
        spawnTerrain("dessert")
    spawnTerrain("desertmtn")
    # mountains generate first so things can overwrite them
    for i in range(2):
        spawnTerrain("forest")
    spawnTerrain("templeruin")
    for i in range(4):
        spawnTerrain("mineruin")
    spawnTerrain("enemy")

    seed[20][15] = 0  # city center of the map


def zoom(event):
    global arraytodel
    zoompercentage = int(event)
    for y in range(0, 29):
        for x in range(0, 39):
            arraytodel[x][y].destroy()
    imageload(zoompercentage)
    render(zoompercentage)


def imageload(size):
    global imagesforgame
    imagesforgame = []
    for load in range(0, 21):
        nameoffile = ("./shittyworldgenimg/", str(load), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((size, size))
        imagestuff = ImageTk.PhotoImage(load)
        imagesforgame.append(imagestuff)
        # print(nameoffile) lags too much while zooming


def spawnTerrain(terrainname):
    global seed
    global rendershit
    number = 1
    loop = True
    rand = 0
    x = randomino.randint(10, 30)
    y = randomino.randint(10, 20)
    if terrainname == "forest":
        print("forset x:" + str(x) + "y:" + str(y))
        number = 9
        rand = randomino.randint(20, 40)
        loop = True
    elif terrainname == "dessert":
        print("desert x:" + str(x) + "y:" + str(y))
        number = 2
        rand = randomino.randint(30, 60)
        loop = True
    elif terrainname == "grassmtn":
        print("grassmtn x:" + str(x) + "y:" + str(y))
        number = 5
        loop = False
        for i in range(2):
            x = randomino.randint(5, 35)
            y = randomino.randint(5, 25)
            seed[x][y] = number
            if x - 1 >= 5 and y - 1 >= 5 and x + 1 <= 35 and y + 1 <= 25:
                seed[x - 1][y] = number
                seed[x - 2][y] = number
                seed[x + 1][y] = number
            x = randomino.randint(5, 35)
            y = randomino.randint(5, 25)
            seed[x][y] = number
            if 5 <= x + 1 <= 35 and y + 1 <= 25 and y - 1 >= 5:
                seed[x][y + 1] = number
                seed[x][y + 2] = number
                seed[x][y - 1] = number
    elif terrainname == "enemy":
        for i in range(randomino.randint(10, 20)):
            x = randomino.randint(1, 36)
            y = randomino.randint(1, 28)
            print("city x:" + str(x) + "y:" + str(y))
            if seed[x][y] == 2:
                number = 12
            elif seed[x][y] == 1 or seed[x][y] == 3:
                number = 11
            seed[x][y] = number
            loop = False
    elif terrainname == "templeruin" or terrainname == "desertmtn" or terrainname == "mineruin":
        found = False
        if terrainname == "templeruin":
            number = 19
        elif terrainname == "mineruin":
            number = 7
        elif terrainname == "desertmtn":
            number = 6
        for exactly in range(0, 39):
            if not found:
                for whynot in range(0, 29):
                    if seed[exactly][whynot] == 2:
                        print("desert found at" + str(exactly) + " " + str(whynot))
                        seed[x][y] = number
                        if terrainname == "desertmtn":
                            for i in range(2):
                                x = randomino.randint(5, 35)
                                y = randomino.randint(5, 25)
                                seed[x][y] = number
                                if x - 1 >= 5 and y - 1 >= 5 and x + 1 <= 35 and y + 1 <= 25:
                                    seed[x - 1][y] = number
                                    seed[x - 2][y] = number
                                    seed[x + 1][y] = number
                                x = randomino.randint(5, 35)
                                y = randomino.randint(5, 25)
                                seed[x][y] = number
                                if 5 <= x + 1 <= 35 and y + 1 <= 25 and y - 1 >= 5:
                                    seed[x][y + 1] = number
                                    seed[x][y + 2] = number
                                    seed[x][y - 1] = number
                        found = True
                        break
            else:
                break
        loop = False
        rendershit = True
    if loop:
        for i in range(rand):
            if 35 >= x >= 5 and 25 >= y >= 5:
                seed[x][y] = number
                if x - 1 >= 5 and y - 1 >= 5:
                    seed[x - 1][y - 1] = number
                if x + 1 <= 35 and y + 1 <= 25:
                    seed[x + 1][y + 1] = number
                if x + 1 >= 5 and y + 1 <= 25:
                    seed[x - 1][y + 1] = number
                if x + 1 <= 35 and y - 1 >= 5:
                    seed[x + 1][y - 1] = number
                if x - 1 >= 5:
                    seed[x - 1][y] = number
                if x + 1 <= 35:
                    seed[x + 1][y] = number
                if y + 1 <= 25:
                    seed[x][y + 1] = number
                if y - 1 >= 5:
                    seed[x][y - 1] = number
                bcd = randomino.randint(0, 3)
                if bcd == 0:
                    x -= randomino.randint(0, 2)
                elif bcd == 1:
                    x += randomino.randint(0, 2)
                elif bcd == 2:
                    y -= randomino.randint(0, 2)
                elif bcd == 3:
                    y += randomino.randint(0, 2)
            '''for b in range(len(usedcenters[0])):
                if x - usedcenters[b] >= 20 or x - usedcenters[b] <= -20:
                    if y - usedcenters[0][b]
                    calculate distance from anotehr center
                    '''


def change(argx, argy):
    global seed
    global bsize
    if seed[argx][argy] == 16:
        seed[argx][argy] = seed[argx][argy] + randomino.randint(1, 2)
    elif seed[argx][argy] == 17 or seed[argx][argy] == 18:
        seed[argx][argy] = 16
    elif seed[argx][argy] == 7:
        seed[argx][argy] = 8
    elif seed[argx][argy] == 8:
        seed[argx][argy] = 7
    elif seed[argx][argy] == 19:
        seed[argx][argy] = 20
    elif seed[argx][argy] == 20:
        seed[argx][argy] = 19
    if seed[argx][argy] == 16 or seed[argx][argy] == 17 or seed[argx][argy] == 18 or seed[argx][argy] == 7 or \
            seed[argx][argy] == 8 or seed[argx][argy] == 19 or seed[argx][argy] == 20:
        arraytodel[argx][argy].destroy()
        a = tk.Button(window, image=imagesforgame[seed[argx][argy]], command=partial(change, argx=argx, argy=argy))
        a.place(x=argx * bsize, y=argy * bsize)
        arraytodel[argx][argy] = a


# have player pick the spot to start off

def render(size):
    global bsize
    bsize = size
    ypos = tk.Label(window, text=("Ypos\n" + str(yloc)))
    ypos.place(x=800, y=420, anchor=tk.NW)
    # print(seed)  too laggy while rendering
    for yy in range(600//int(size)):
        for xx in range(800//int(size)):
            a = tk.Button(window, image=imagesforgame[seed[xx][yy]], command=partial(change, argx=xx, argy=yy))
            a.place(x=xx * size, y=yy * size)
            arraytodel[xx][yy] = a
    zoomscale = tk.Scale(window, from_=20, to=100, orient=tk.HORIZONTAL, command=zoom)
    zoomscale.place(x=0, y=590, anchor=tk.NW)
    textforzoom = tk.Label(window, text=("Zoom current size:" + str(size)))
    textforzoom.place(x=0, y=585, anchor=tk.NW)
    xScale = tk.Scale(window, from_=0, to=800, orient=tk.HORIZONTAL)
    xScale.place(x=700, y=590, anchor=tk.NW)
    xpos = tk.Label(window, text=("Xpos\n" + str(xloc)))
    xpos.place(x=625, y=585, anchor=tk.NW)
    yScale = tk.Scale(window, from_=800, to=0, orient=tk.VERTICAL)
    yScale.place(x=790, y=470, anchor=tk.NW)



'''
def printSave():
    a = []
    for x in range(0, 40):
        for y in range(0, 30):
            a.append(seed[x][y])
    print(('{} ' * len(a)).format(*a))
'''

'''
def loadcode(inpt):
    global arraytodel
    global seed
    a = inpt
    counter = 0
    for i in range(39):
        for ix in range(29):
            arraytodel[i][ix].destroy()
    for y in range(0, 29):
        for x in range(0, 39):
            seed[x][y] = int(a[counter])
            counter += 1


#inputs = tk.Entry()
#inputs.place(x=0, y=600, anchor=tk.NW)
#loadbtn = tk.Button(window, text="load", command=lambda: [loadcode(inputs.get())])
#loadbtn.place(x=200, y=600, anchor=tk.NW)
#savebtn = tk.Button(window, text="save", command=printSave)
#savebtn.place(x=700, y=600, anchor=tk.NW)
'''

if __name__ == '__main__':
    main()
    render(20)
    tk.mainloop()

'''

the print format:

land -> ocean (10,11)

x = 40 x 20
y = 30 x 20

0 flat land (grass) [may spawn enemy territory]
1 plains [cattle and herding]
2 grass mtn [a great inconvenience]
3 forest [wood]
4 enemy city (grass)
5 flat land (desert) [mines from scratch, temples from scratch]
6 enemy city (desert)
7 desert mtn [mines]
8 mines (ruin)
9 mine [gold]
10 temple (ruin)
11 temple [magic and happiness]
12 grass near beach 
13 beach near ocean
14 dock 
15 your city
'''
