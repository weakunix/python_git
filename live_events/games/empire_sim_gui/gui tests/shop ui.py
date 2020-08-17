import random
import tkinter as tk
from PIL import Image, ImageTk
from functools import partial
from tkinter import messagebox
from tkinter import messagebox  # messagebox must be explicitly imported

# make window window
window = tk.Tk()
window.geometry("800x600")
window.title("royadle")

# variables
castleName = "CowlandBingBing"
solddata = [  # example of what sold in format
    ["Cowland", "Wood", 1000, 10],  # castle from, what sold, how many, money per
    ["Eagle Claw Nation", "Food", 10, 10],  # castle from, what sold, how many, money per
    [False, "Fragment", 1, 1000]  # no castle (wandering trader), selling magic fragment(1) for (1000)
]
materials = [
    0,  # else statement
    10000,  # wood
    100,  # rock
    100,  # metal
    10000  # food
]
pricing = [
    0,
    4,
    6,
    10,
    5
]
castles = [
    "cowland",
    "mootbing",
    "botmooo",
    "llqqdd",
    "royadle"
]
imagesforgame = []
buyamt = [0, 0, 0]


def imageload():
    global imagesforgame
    imagesforgame = []
    for loadd in range(0, 6):
        nameoffile = ("./shittyworldgenimg/mat", str(loadd), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((100, 100))
        imagestuff = ImageTk.PhotoImage(load)
        imagesforgame.append(imagestuff)
    nameoffile = "./shittyworldgenimg/mat0.png"
    load = Image.open(nameoffile)
    load = load.resize((350, 350))
    imagestuff = ImageTk.PhotoImage(load)
    imagesforgame.append(imagestuff)
    for loadd in range(3, 6):
        nameoffile = ("./shittyworldgenimg/mat", str(loadd), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((350, 350))
        imagestuff = ImageTk.PhotoImage(load)
        imagesforgame.append(imagestuff)


imageload()


# button destroy
def destroybtn(*destroys, **kwargs):
    delsarry = kwargs.get("ary", None)
    try:
        for i in range(len(delsarry)):
            delsarry[i].destroy()
    except:
        pass
    for args in destroys:
        args.destroy()


def change(ab, ai, arry):
    global solddata
    global buyamt
    if ab:
        destroybtn(ary=arry)
        solddata[ai][2] -= int(buyamt[0])
        pageo()


def setsomething(event):
    global buyamt
    buyamt[0] = event


def pageo():
    delarray = []
    whereToPlace = [
        [200, 75],
        [400, 75],
        [200, 300],
        [400, 300],
        [0, 75],
        [600, 75],
        [0, 300],
        [600, 300]
    ]
    whereToPlacetxt = [
        [25, 2],
        [25, 120],
        [10, 145],
        [120, 185],
        [10, 170]
    ]
    deldeal = []
    for i in range(len(solddata)):
        if solddata[i][2] != 0:
            texts = [
                solddata[i][0],
                solddata[i][1],
                ("Amount:" + str(solddata[i][2]) + " $" + str(solddata[i][3])),
                0,
                "Buy"
            ]
            texts[0] = "Merchant" if texts[0] == 0 else texts[0]
            offer = tk.Button(window, text="", width=17, height=13)
            offer.place(x=whereToPlace[i][0], y=whereToPlace[i][1])
            img = 0 if solddata[i][1] == "Food" else 5 if solddata[i][1] == "Metal" else 4 if solddata[i][
                                                                                                  1] == "Stone" else 3 if \
                solddata[i][1] == "Wood" else 1
            # img = 0 if solddata[i][1] == "Food" else 3 if solddata[i][1] == "Wood" else 1
            offerimg = tk.Button(window, image=imagesforgame[img])
            offerimg.place(x=whereToPlace[i][0] + 25, y=whereToPlace[i][1] + 20)
            howmuch = tk.Scale(window, from_=0, to=solddata[i][2], orient=tk.HORIZONTAL, command=setsomething)
            howmuch.place(x=whereToPlace[i][0] + whereToPlacetxt[4][0],
                          y=whereToPlace[i][1] + whereToPlacetxt[4][1])
            buy = tk.Button(window, text=texts[4],
                            command=partial(change, ab=True, arry=delarray, ai=i))
            buy.place(x=whereToPlace[i][0] + whereToPlacetxt[3][0], y=whereToPlace[i][1] + whereToPlacetxt[3][1])
            for b in range(0, 3):
                info = tk.Label(window, text=texts[b])
                info.place(x=whereToPlace[i][0] + whereToPlacetxt[b][0], y=whereToPlace[i][1] + whereToPlacetxt[b][1])
                delarray.extend((offerimg, offer, info, howmuch, buy))
        else:
            deldeal.append(i)
    offersText = tk.Label(window, text="Offers:")
    offersText.config(font=("Courier", 44))
    offersText.place(x=400, y=25, anchor=tk.CENTER)
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                     command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
    Home.place(x=0, y=0, anchor=tk.NW)
    nexxt = tk.Button(window, text=">",
                      command=lambda: [paget(123), destroybtn(nexxt, Home, offersText, ary=delarray)])
    nexxt.place(x=500, y=550, anchor=tk.CENTER)
    for i in range(len(deldeal)):
        solddata[deldeal[i]] = [0, 0, 0, 0]  # turns into empty deal


def setsomethingelse(event):
    global buyamt
    buyamt[1] = event


def setsomethingelsee(event):
    global buyamt
    buyamt[2] = event


def sell(selectedG, selectedC):
    global solddata, buyamt  # TODO ruoyu remove this later so you wont beable to buy your own items lol
    if selectedG.get() != "Pick The Material" and selectedC.get != "Pick The Castle To Sell To" and buyamt[1] != 0 and \
            buyamt[2] != 0:
        brr = False
        for i in range(len(solddata)):
            if [0, 0, 0, 0] in solddata:
                brr = True
                solddata[i] = ([castleName, selectedG.get(), buyamt[1], buyamt[2]])
        if not brr:
            solddata.append([castleName, selectedG.get(), buyamt[1], buyamt[2]])

deletearray = []


def paget(*args):
    global deletearray
    tf = args[0]
    options = [
        "Wood",
        "Stone",
        "Metal",
        "Food"
    ]
    say = [
        ["Send To:", 530, 400],
        ["Price:", 550, 270],
        ["Amount:", 540, 320],
        ["Goods To Sell:", 550, 200]
    ]
    top = 4 if tf == "Food" else 3 if tf == "Metal" else 2 if tf == "Stone" else 1 if tf == "Wood" else 0
    howmuchgive = tk.Scale(window, from_=0, to=materials[top],
                           orient=tk.HORIZONTAL,
                           command=setsomethingelse)  # TODO 1000 change to material variable array thingy
    howmuchgive.place(x=600, y=300)
    howmuchsell = tk.Scale(window, from_=0, to=(materials[top] * pricing[top] * 2),
                           orient=tk.HORIZONTAL,
                           command=setsomethingelsee)  # TODO RUOYU CHANGE HOW HIGH IT CAN GO TO. MAX IS 5% OF YOUR THING
    howmuchsell.place(x=600, y=250)
    deletearray.extend((howmuchsell, howmuchgive))
    if tf == 123:
        padding = tk.Button(window, text="", width=40, height=20)
        padding.place(x=490, y=150)
        selectedG = tk.StringVar()
        selectedG.set("Pick The Material")
        selectedC = tk.StringVar()
        selectedC.set("Pick The Castle To Sell To")
        dropgift = tk.OptionMenu(window, selectedG, *options, command=paget)
        dropgift.place(x=650, y=200)
        dropcastle = tk.OptionMenu(window, selectedC, *castles)
        dropcastle.place(x=600, y=400)
        confirm = tk.Button(window, text="Confirm",
                            command=lambda: [sell(selectedG, selectedC)])
        confirm.place(x=610, y=440)
        for i in range(len(say)):
            label = tk.Label(window, text=say[i][0])
            label.place(x=say[i][1], y=say[i][2])
            deletearray.append(label)
        Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                         command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
        Home.place(x=0, y=0, anchor=tk.NW)
        last = tk.Button(window, text="<",
                         command=lambda: [pageo(),
                                          destroybtn(last, Home, padding, dropgift, confirm, dropgift, dropcastle,
                                                     howmuchgive, howmuchsell, ary=deletearray)])
        last.place(x=300, y=550, anchor=tk.CENTER)
    else:
        img = 6 if tf == "Food" else 9 if tf == "Metal" else 8 if tf == "Stone" else 7
        imgthing = tk.Button(window, image=imagesforgame[img])
        imgthing.place(x=50, y=120)
        deletearray.append(imgthing)


# launch main loop
if __name__ == "__main__":
    pageo()
    window.mainloop()
