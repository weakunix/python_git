import random as randomino
import tkinter as tk
from PIL import Image, ImageTk
from functools import partial
from tkinter import messagebox

window = tk.Tk()
window.configure(bg="cyan")  # background of the window
window.geometry("840x630")
imagesforgame = []
clansimages = []
clans = [
    "naibings",
    "bulls",
    "cows",
    "bingers",
    "moot"
]
usedcenters = [[]]
pathdelarray = []
planningPath = False
seed = [[0 for y in range(30)] for x in range(40)]
pathfind = [[0 for yyy in range(30)] for xxx in range(40)]
pathcoords = []
rendershit = False
arraytodel = [[0 for yyyy in range(30)] for xxxx in range(40)]
clandict = {}
bsize = 0
xloc = 0
turn = 1
yloc = 0
attacking = False
castleLoc = (0, 0)
castlenames = [
    "mootbing",
    'nailand',
    'mootluz',
    'skairm',
    'cowland',
    'mooland',
    'botland'
]


def wintitle():
    d = (clans[randomino.randint(0, len(clans) - 1)], castlenames[randomino.randint(0, len(castlenames) - 1)])
    window.title(":".join(d))


deletethesewidgets = []


def resetBTNSLIDER(a):
    global deletethesewidgets
    global xloc
    global yloc
    xloc = 0
    yloc = 0
    if len(deletethesewidgets) != 0:
        for i in range(len(deletethesewidgets)):
            deletethesewidgets[i].destroy()
    if a:
        zoomscale = tk.Scale(window, from_=20, to=100, orient=tk.HORIZONTAL, command=zoom)
        zoomscale.place(x=0, y=590, anchor=tk.NW)
        # deletethesewidgets.append(zoomscale)
    yScale = tk.Scale(window, from_=24, to=0, orient=tk.VERTICAL, command=changelocy)
    yScale.place(x=790, y=470, anchor=tk.NW)
    deletethesewidgets.append(yScale)
    xScale = tk.Scale(window, from_=0, to=32, orient=tk.HORIZONTAL, command=changelocx)
    xScale.place(x=700, y=590, anchor=tk.NW)
    deletethesewidgets.append(xScale)


def main():
    global seed
    global castleLoc
    global rendershit
    global arraytodel
    global imagesforgame
    loadcastle(40)
    resetBTNSLIDER(True)
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
    castleLoc = castleplace()
    seed[castleLoc[0]][castleLoc[1]] = 0


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


def loadcastle(size):
    global clansimages
    clansimages = []
    for load in range(1, 6):
        nameoffile = ("./shittyworldgenimg/clan", str(load), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((size, size))
        tempimg = ImageTk.PhotoImage(load)
        clansimages.append(tempimg)


def imageload(size):
    global imagesforgame
    imagesforgame = []
    for load in range(0, 27):
        nameoffile = ("./shittyworldgenimg/", str(load), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((size, size))
        imagestuff = ImageTk.PhotoImage(load)
        imagesforgame.append(imagestuff)
    # print(clansimages)


def spawnTerrain(terrainname):
    global seed
    global rendershit
    global clandict
    number = 1
    loop = True
    rand = 0
    x = randomino.randint(10, 30)
    y = randomino.randint(10, 20)
    if terrainname == "forest":
        # print("forset x:" + str(x) + "y:" + str(y))
        number = 9
        rand = randomino.randint(20, 40)
        loop = True
    elif terrainname == "plains":
        number = 10
        rand = randomino.randint(10, 20)
        loop = True
    elif terrainname == "dessert":
        # print("desert x:" + str(x) + "y:" + str(y))
        number = 2
        rand = randomino.randint(30, 60)
        loop = True
    elif terrainname == "grassmtn":
        # print("grassmtn x:" + str(x) + "y:" + str(y))
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
            clandict[(returntuple[0], returntuple[1])] = (
                clans[randomino.randint(0, (len(clans) - 2))],
                castlenames[randomino.randint(0, (len(castlenames) - 2))])
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


def destroybtn(*destroys):
    for args in destroys:
        args.destroy()


def showallclans(aname, img, arg):
    for xasd in range(40):
        for yasd in range(30):
            if (xasd, yasd) in clandict:
                clans = clandict[(xasd, yasd)]
                clans = clans[0]
                if clans == aname:
                    if arg:
                        loadcastle(20)
                        seed[xasd + xloc][yasd + yloc] = 11
                        arraytodel[xasd + xloc][yasd + yloc].destroy()
                        clanshow = tk.Button(window, image=img,
                                             command=lambda: [showallclans(aname, img, False),
                                                              destroybtn(clanshow)])
                        clanshow.place(x=xasd * bsize, y=yasd * bsize)
                        arraytodel[xasd + xloc][yasd + yloc] = clanshow
                    else:
                        loadcastle(40)
                        img = imagesforgame[11]
                        seed[xasd + xloc][yasd + yloc] = 11
                        render(bsize, xloc, yloc)


def imgtheclan(aname):
    bname = aname[1]
    aname = aname[0]
    ret = ""
    if aname == "naibings":
        ret = clansimages[0]
    elif aname == "bulls":
        ret = clansimages[1]
    elif aname == "cows":
        ret = clansimages[2]
    elif aname == "bingers":
        ret = clansimages[3]
    elif aname == "moot":
        ret = clansimages[4]
    return ret, bname, aname


def retreatmsg(aray, armyspyordip, turnspermove):
    background = tk.Button(window, text="", width=13, height=2)
    background.place(x=400, y=300, anchor=tk.CENTER)
    retreatbtn = tk.Button(window, text="Retreat",
                           command=lambda: [ataktroops(True, aray, armyspyordip, howmuchgoupdown=-3),
                                            destroybtn(background, retreatbtn, fastbtn)])
    retreatbtn.place(x=375, y=300, anchor=tk.CENTER)
    fastbtn = tk.Button(window, text="Boost",
                        command=lambda: [ataktroops(True, aray, armyspyordip, howmuchgoupdown=turnspermove+1),
                                         destroybtn(background, retreatbtn, fastbtn)])
    fastbtn.place(x=430, y=300, anchor=tk.CENTER)


def ataktroops(tf, aray, armyspyormat, **kwargs):
    global attacking
    global turn
    turnincrease = 1
    if tf or attacking:
        try:
            turnincrease = kwargs.get("howmuchgoupdown", None)
        except:
            pass
        finally:
            attacking = True
            '''try:'''
            imgn = 0
            if armyspyormat == "spy":
                imgn = imagesforgame[25]
            elif armyspyormat == "atk":
                imgn = imagesforgame[24]
            elif armyspyormat == "mat":
                imgn = imagesforgame[26]
            attacktroops = tk.Button(window, image=imgn, command=lambda: [retreatmsg(aray, armyspyormat, turnincrease), destroybtn(attacktroops)])
            if turnincrease is None:
                turnincrease = 1
            location = (0, 0)
            if turn >= len(aray) or turn < 0:
                turn = 1
                attacking = False
            else:
                location = aray[turn]
                turn += turnincrease
                attacktroops.place(x=location[0] * bsize, y=location[1] * bsize)
                nextturnbtn = tk.Button(window, text="next turn", command=lambda: [
                    ataktroops(tf, aray, armyspyormat, howmuchgoupdown=turnincrease),
                    destroybtn(nextturnbtn, attacktroops)])
                nextturnbtn.place(x=500, y=600, anchor=tk.NW)


def stopath(confirm, armyspyormat):
    global planningPath
    global pathdelarray
    global pathfind
    global pathcoords
    if confirm:
        for a in range(0, 40):
            for b in range(0, 30):
                # try:
                if 1 <= a <= 38 and 1 <= b <= 28:
                    if pathfind[a][b - 1] == 2 or pathfind[a - 1][b - 1] == 2 or pathfind[a - 1][b] == 2 or \
                            pathfind[a + 1][b - 1] == 2 or pathfind[a + 1][b] == 2 or pathfind[a + 1][b + 1] == 2 or \
                            pathfind[a][b + 1] == 2 or pathfind[a - 1][b + 1] == 2:
                        if pathfind[a][b] == 1:
                            msg = tk.messagebox.askyesno("go to castle", "Are you sure you want to go to this castle?")
                            if msg:
                                ataktroops(True, pathcoords, armyspyormat)
                                # print("loc" + str(pathcoords))
                                # print(str(pathcoords[turn]))
                                pathcoords = []
                # except:
                # print("uhoh")
    planningPath = False
    for i in range(len(pathdelarray)):
        pathdelarray[i].destroy()


def popcoord(x, y):
    global pathcoords
    pathcoords.pop()


def planpath(ax, ay, T, **kwargs):
    global planningPath
    global pathfind
    global pathdelarray
    global pathcoords
    if not T:
        if seed[ax][ay] != 5 and seed[ax][ay] != 6:  # not mountains
            if planningPath:
                if pathfind[ax][ay - 1] == 1 or pathfind[ax - 1][ay - 1] == 1 or pathfind[ax - 1][ay] == 1 or \
                        pathfind[ax + 1][ay - 1] == 1 or pathfind[ax + 1][ay] == 1 or pathfind[ax + 1][ay + 1] == 1 or \
                        pathfind[ax][ay + 1] == 1 or pathfind[ax - 1][ay + 1] == 1:
                    planningPath = True
                    path = tk.Button(window, image=imagesforgame[23],
                                     command=lambda: [destroybtn(path), popcoord(ax, ay)])
                    path.place(x=ax * bsize, y=ay * bsize)
                    pathdelarray.append(path)
                    pathcoords.append((ax, ay))
                    for xxa in range(40):  # cant branch out from random places
                        for yya in range(30):
                            if pathfind[xxa][yya] == 1:
                                pathfind[xxa][yya] = 2
                    pathfind[ax][ay] = 1
    elif T:
        armyspyormat = kwargs.get('armyspyormat', None)
        planningPath = True
        enemybase = tk.Button(window, image=imagesforgame[21],
                              command=lambda: [stopath(True, armyspyormat),
                                               destroybtn(homebase, enemybase)])
        enemybase.place(x=ax * bsize, y=ay * bsize)
        planningPath = True
        homebase = tk.Button(window, image=imagesforgame[22],
                             command=lambda: [stopath(False, armyspyormat),
                                              destroybtn(homebase, enemybase)])
        homebase.place(x=castleLoc[0] * bsize, y=castleLoc[1] * bsize)
        pathcoords.append((castleLoc[0], castleLoc[1]))
        pathfind[castleLoc[0]][castleLoc[1]] = 1
        pathfind[ax][ay] = 2


def popup(ax, ay):
    print("popuped")
    ayloc = 0
    axloc = 0
    if ax <= 4:
        axloc = 4
    elif ax >= 35:
        axloc = 35
    elif bsize == 20:
        axloc = ax
    else:
        axloc = 4  # not worth the hassle to attach to castle zoomed in
    if ay <= 4:
        ayloc = 4
    elif bsize == 20:
        ayloc = ay
    else:
        ayloc = 4
    clanname = ""
    if (ax, ay) in clandict:
        clanname = imgtheclan(clandict[(ax, ay)])
    csize = 20
    background = tk.Button(window, text="", width=22, height=5)
    background.place(x=axloc * csize + csize / 2, y=ayloc * csize + 5, anchor=tk.S)
    label = tk.Label(window, text=(clanname[1] + "\nat: \nx:" + str(ax) + " y:" + str(ay)))
    label.place(x=axloc * csize - 55, y=ayloc * csize - 20, anchor=tk.S)
    op1 = tk.Button(window, text="Spy",
                    command=lambda: [planpath(ax, ay, True, armyspyormat="spy"),
                                     destroybtn(background, op1, op2, op3, label, cancl,
                                                label2, clanimg)])
    op1.place(x=axloc * csize - 65, y=ayloc * csize - csize / 2, anchor=tk.CENTER)
    op2 = tk.Button(window, text="Attack",
                    command=lambda: [planpath(ax, ay, True, armyspyormat="atk"),
                                     destroybtn(background, op1, op2, op3, label, cancl,
                                                label2, clanimg)])
    op2.place(x=axloc * csize - 23, y=ayloc * csize - csize / 2, anchor=tk.CENTER)
    op3 = tk.Button(window, text="Send Materials",
                    command=lambda: [planpath(ax, ay, True, armyspyormat="mat"),
                                     destroybtn(background, op1, op2, op3, label, cancl,
                                                label2, clanimg)])
    op3.place(x=axloc * csize + 52, y=ayloc * csize - csize / 2, anchor=tk.CENTER)
    label2 = tk.Label(window, text="Clan:")
    label2.place(x=axloc * csize, y=ayloc * csize - 60, anchor=tk.CENTER)
    clanimg = tk.Button(window, image=clanname[0], command=lambda: [showallclans(clanname[2], clanname[0], True),
                                                                    destroybtn(background, op1, op2, op3, label, cancl,
                                                                               label2, clanimg)])
    clanimg.place(x=axloc * csize + 40, y=ayloc * csize - csize * 2.4, anchor=tk.CENTER)
    cancl = tk.Button(window, text="Exit\nMenu", height=3,
                      command=lambda: [destroybtn(background, op1, op2, op3, label, cancl, label2, clanimg)])
    cancl.place(x=axloc * csize + 85, y=ayloc * csize - csize * 2.4, anchor=tk.CENTER)


def change(argx, argy):
    print(argx, argy)
    global seed
    global bsize
    global planningPath
    if not planningPath:
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
            popup(argx, argy)
            # msg = tk.messagebox.askyesno("Options", "Attack? Spy? Send Material?")
        if seed[argx][argy] == 16 or seed[argx][argy] == 17 or seed[argx][argy] == 18 or seed[argx][argy] == 7 or \
                seed[argx][argy] == 8 or seed[argx][argy] == 19 or seed[argx][argy] == 20:
            arraytodel[argx][argy].destroy()
            a = tk.Button(window, image=imagesforgame[seed[argx][argy]], command=partial(change, argx=argx, argy=argy))
            a.place(x=argx * bsize, y=argy * bsize)
            arraytodel[argx][argy] = a
            render(bsize, xloc, yloc)
    else:
        planpath(argx, argy, False)


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
                              command=partial(change, argx=xx + locx, argy=yy + locy))  # TODO newline here fix
                a.place(x=xx * size, y=yy * size)
                arraytodel[xx + locx][yy + locy] = a
            except:
                print("indexoutofrange")
    textforzoom = tk.Label(window, text=("Zoom current size:" + str(size)))
    textforzoom.place(x=100, y=600, anchor=tk.NW)
    xpos = tk.Label(window, text=("Xpos\n" + str(xloc)))
    xpos.place(x=625, y=585, anchor=tk.NW)
    deletethesewidgets.append(textforzoom)
    deletethesewidgets.append(xpos)
    deletethesewidgets.append(ypos)


if __name__ == '__main__':
    wintitle()
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
