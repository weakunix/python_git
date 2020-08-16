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
solddata = [  # example of what sold in format
    ["Cowland", "Materials", 1000, 10],  # castle from, what sold, how many, money per
    ["Eagle Claw Nation", "Food", 10, 10],  # castle from, what sold, how many, money per
    [False, "Fragment", 1, 1000]  # no castle (wandering trader), selling magic fragment(1) for (1000)
]
imagesforgame = []


def imageload():
    global imagesforgame
    imagesforgame = []
    for load in range(0, 3):
        nameoffile = ("./shittyworldgenimg/mat", str(load), ".png")
        nameoffile = "".join(nameoffile)
        load = Image.open(nameoffile)
        load = load.resize((100, 100))
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


# place button
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
        [10, 170],
        [120, 185]
    ]
    for i in range(len(solddata)):
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
        #print("no") if x > 42 else print("yes") if x == 42 else print("maybe") lmao 1 liners
        img = 0 if solddata[i][1] == "Food" else 2 if solddata[i][1] == "Materials" else 1
        offerimg = tk.Button(window, image=imagesforgame[img])
        offerimg.place(x=whereToPlace[i][0] + 25, y=whereToPlace[i][1] + 20)
        for b in range(0, 5):
            if b == 3:
                howmuch = tk.Scale(window, from_=0, to=solddata[i][2], orient=tk.HORIZONTAL)
                howmuch.place(x=whereToPlace[i][0] + whereToPlacetxt[b][0],
                              y=whereToPlace[i][1] + whereToPlacetxt[b][1])
                delarray.extend((offerimg, offer, howmuch))
            else:
                info = tk.Label(window, text=texts[b])
                info.place(x=whereToPlace[i][0] + whereToPlacetxt[b][0], y=whereToPlace[i][1] + whereToPlacetxt[b][1])
                delarray.extend((offerimg, offer, info))
    offersText = tk.Label(window, text="Offers:")
    offersText.config(font=("Courier", 44))
    offersText.place(x=400, y=25, anchor=tk.CENTER)
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                     command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
    Home.place(x=0, y=0, anchor=tk.NW)
    nexxt = tk.Button(window, text=">",  # make load button
                      command=lambda: [paget(), destroybtn(nexxt, Home, offersText, ary=delarray)])
    nexxt.place(x=500, y=550, anchor=tk.CENTER)


def paget():
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                     command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
    Home.place(x=0, y=0, anchor=tk.NW)
    last = tk.Button(window, text="<",  # make delete save button
                     command=lambda: [pageo(), destroybtn(last, Home)])
    last.place(x=300, y=550, anchor=tk.CENTER)


# launch main loop
if __name__ == "__main__":
    pageo()
    window.mainloop()
