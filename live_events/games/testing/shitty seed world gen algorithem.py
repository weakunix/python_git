import random as randomino
import tkinter as tk
from PIL import Image, ImageTk
from functools import partial
from tkinter import messagebox

window = tk.Tk()
window.title("wow this is actually starting to impress myself")
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
deletethesewidgets = []


def resetBTNSLIDER(a):
    global deletethesewidgets
    global xloc
    global yloc
    xloc = 0
    yloc = 0
    if a:
        zoomscale = tk.Scale(window, from_=20, to=100, orient=tk.HORIZONTAL, command=zoom)
        zoomscale.place(x=0, y=590, anchor=tk.NW)
        deletethesewidgets.append(zoomscale)
    yScale = tk.Scale(window, from_=24, to=0, orient=tk.VERTICAL, command=changelocy)
    yScale.place(x=790, y=470, anchor=tk.NW)
    deletethesewidgets.append(yScale)
    xScale = tk.Scale(window, from_=0, to=32, orient=tk.HORIZONTAL, command=changelocx)
    xScale.place(x=700, y=590, anchor=tk.NW)
    deletethesewidgets.append(xScale)


def main():
    resetBTNSLIDER(True)
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
    spawnTerrain("plains")
    for i in range(2):
        spawnTerrain("forest")
    for i in range(4):
        spawnTerrain("mineruin")
    spawnTerrain("templeruin")
    spawnTerrain("enemy")
    returntuple = castleplace()
    seed[returntuple[0]][returntuple[1]] = 0


def castleplace():
    if randomino.randint(0, 1):
        xcastle = randomino.randint(0, 5)
    else:
        xcastle = randomino.randint(32, 37)
    if randomino.randint(0, 1):
        ycastle = randomino.randint(0, 5)
    else:
        ycastle = randomino.randint(24, 29)
    return xcastle, ycastle


def zoom(event):
    zoompercentage = int(event)
    imageload(zoompercentage)
    resetBTNSLIDER(False)
    render(zoompercentage, 0, 0)


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
    elif terrainname == "plains":
        number = 10
        rand = randomino.randint(10, 20)
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
            returntuple = castleplace()
            if seed[returntuple[0]][returntuple[1]] == 2:
                number = 12
            else:
                number = 11
            seed[returntuple[0]][returntuple[1]] = number
            loop = False
    elif terrainname == "desertt":
        number = 2
        rand = randomino.randint(10, 20)
        loop = True
    elif terrainname == "templeruin":
        spawnTerrain("desertt")
        seed[20][15] = 19
    elif terrainname == "desertmtn" or terrainname == "mineruin":
        found = False
        if terrainname == "mineruin":
            number = 7
        elif terrainname == "desertmtn":
            number = 6
        havefoundx = []
        havefoundy = []
        build = True
        for exactly in range(0, 39):
            if not found:
                for whynot in range(0, 29):
                    if seed[exactly][whynot] == 2:
                        for ala in range(len(havefoundx)):
                            for blb in range(len(havefoundy)):
                                if havefoundy[blb] == whynot and havefoundx[ala] == exactly:
                                    build = False
                        if build:
                            print("desert found at" + str(exactly) + " " + str(whynot))
                            seed[x][y] = number
                            havefoundx.append(x)
                            havefoundy.append(y)
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
            if terrainname == "dessert":
                number = randomino.randint(0, 10)
                if number == 0:
                    number = 4
                else:
                    number = 2
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


def change(argx, argy):
    global seed
    global bsize
    argx += xloc
    argy += yloc
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
    elif seed[argx][argy] == 12 or seed[argx][argy] == 11:
        msg = tk.messagebox.askyesno("Options", "Attack? Spy? Send Material?")
    if seed[argx][argy] == 16 or seed[argx][argy] == 17 or seed[argx][argy] == 18 or seed[argx][argy] == 7 or \
            seed[argx][argy] == 8 or seed[argx][argy] == 19 or seed[argx][argy] == 20:
        arraytodel[argx][argy].destroy()
        a = tk.Button(window, image=imagesforgame[seed[argx][argy]], command=partial(change, argx=argx, argy=argy))
        a.place(x=argx * bsize, y=argy * bsize)
        arraytodel[argx][argy] = a
        render(bsize, xloc, yloc)


def changelocx(event):
    global bsize
    global xloc
    global yloc
    xloc = int(event)
    render(bsize, xloc, yloc)


def changelocy(event):
    global bsize
    global xloc
    global yloc
    yloc = int(event)
    render(bsize, xloc, yloc)


# have player pick the spot to start off

def render(size, locx, locy):
    global bsize
    global arraytodel
    global deletethesewidgets
    for i in range(len(deletethesewidgets)):
        deletethesewidgets[i].destroy
    if arraytodel[0][0] != 0:
        for y in range(0, 30):
            for x in range(0, 40):
                if arraytodel[x][y] != 0:
                    arraytodel[x][y].destroy()
        arraytodel = [[0 for y in range(30)] for x in range(40)]
    bsize = size
    ypos = tk.Label(window, text=("Ypos\n" + str(yloc)))
    ypos.place(x=800, y=420, anchor=tk.NW)
    for yy in range(600 // int(size)):
        for xx in range(800 // int(size)):
            try:
                a = tk.Button(window, image=imagesforgame[seed[xx + locx][yy + locy]],
                              command=partial(change, argx=xx, argy=yy))
                a.place(x=xx * size, y=yy * size)
                arraytodel[xx + locx][yy + locy] = a
            except:
                print("indexoutofrange")
    textforzoom = tk.Label(window, text=("Zoom current size:" + str(size)))
    textforzoom.place(x=0, y=585, anchor=tk.NW)
    xpos = tk.Label(window, text=("Xpos\n" + str(xloc)))
    xpos.place(x=625, y=585, anchor=tk.NW)
    deletethesewidgets.append(textforzoom)
    deletethesewidgets.append(xpos)
    deletethesewidgets.append(ypos)


if __name__ == '__main__':
    main()
    render(20, 0, 0)
    tk.mainloop()

'''
the pngs and what they stand for:

0 your castle (always centered)
1 flat land 
2 flat land (desert) [mines from scratch, temples from scratch]
3 flat land with rock (1/10th chance) per grass tile
4 desert land with cactus (1/10th chance) per desert tile
5 grass mtn [a great inconvenience] 
6 desert mtn [mines]
7 mines (ruin)
8 mine [gold]
9 forest [wood]
10 plains (spawns on grass like forest)[cattle and herding]
11 enemy castle grass
12 enemy castle sand
13 grass to sand
14 beach near ocean 
15 dock
16 ocean
17 fishing boat
18 oil derrick
19 temple (ruins)
20 temple (rebuilt)
'''
