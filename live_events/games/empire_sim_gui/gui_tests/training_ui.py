import random
import tkinter as tk
from PIL import Image, ImageTk
import destroything
import matplotlib

matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import platform
from tkinter import messagebox  # messagebox must be explicitly imported

# make window window
window = tk.Tk()
window.geometry("800x600")
window.title("Training")

#                0     1     2        3       4          5       6           7             8          9     10
recruits = [  # name, desc, dmg, fire rate, wood/day, stone/day, metal/day, food/day, wood to make, stone, metal
    ["muscle", "Mr.I did pushups for fun...\n (no he's not on steroids)", 10, 1000, 0, 5, 0, 1, 0, 25, 0],
    ["slingshotty", "Ka-pow... splat\n reload, repeat", 10, 800, 5, 7, 0, 5, 50, 0, 0],
    ["厨师", "One knife is cool, \n Two and you're a chef", 20, 400, 10, 0, 1, 0, 25, 0, 25],
    ["robinhood", "100% accuracy..., \n but the decimal is between 1/0", 40, 500, 10, 20, 0, 10, 25, 50, 0],
    ["princess", "shotgun of the medieval age\n (not CR copy)", 200, 1000, 30, 0, 10, 20, 50, 100, 0],
    ["panini", "Highly trained elite-\n Hmm i wonder what that hat is...", 20, 100, 0, 0, 20, 20, 0, 0, 100],
    ["cannon", "Big round thing that shoots\n (No it doesn't look like a ballsac)", 1000, 2000, 0, 70, 0, 0, 0, 500, 0],
    ["albreto", "Smart man\n albreto scientist", 200, 600, 0, 0, 0, 40, 0, 0, 0]  # albreto cant be trained
]
imagesforgame = []
amnt = 0
new = True
delarray = []


def imageload():
    global imagesforgame
    a = ""
    for i in range(2):
        for b in range(len(recruits)):  # loads all the recruit images and their throwing images too
            # print("./empire_sim_images/", recruits[b], a, ".png")
            nameoffile = ("./shittyworldgenimg/", recruits[b][0], a, ".png")
            nameoffile = "".join(nameoffile)
            load = Image.open(nameoffile)
            imagestuff = ImageTk.PhotoImage(load)
            imagesforgame.append(imagestuff)
        a = "thrown"


imageload()


def switchamt(event, number):
    global amnt
    global delarray
    global new
    new = False
    amnt = event
    destroything.destroyBTN(arry=delarray)
    makeItems(number=number)


def plot(number):
    mats = [
        500,  # wood
        10000,  # rock
        20000,  # metal
        50000  # food
    ]
    datapoints = [
        [mats[0] - recruits[number][8], mats[0] - recruits[number][8] - recruits[number][4]],
        [mats[1] - recruits[number][9], mats[1] - recruits[number][9] - recruits[number][5]],
        [mats[2] - recruits[number][10], mats[2] - recruits[number][10] - recruits[number][6]],
        [mats[3], mats[3] - recruits[number][10] - recruits[number][6]]
    ]
    for i in range(3):
        pass
    plotting = tk.Toplevel(window)
    plotting.title("Graph")
    closeanim = tk.Button(window, text="Close Graph")
    closeanim.place(x=670, y=175, anchor=tk.CENTER)
    fg = plt.Figure(figsize=(5, 4), dpi=100)
    a = fg.add_subplot(111)
    line2 = FigureCanvasTkAgg(fg, plotting)
    line2.get_tk_widget().pack(side=tk.LEFT, fill=tk.BOTH)
    #plt.plot(datapoints[0]-)
    a.set_title('Materials Over Time')


def animate(make, number):
    global new
    if make == "sdf":
        closeanim = tk.Button(window, text="Close Animations Running", command=lambda: [animate("close", closeanim)])
        closeanim.place(x=670, y=175, anchor=tk.CENTER)
        new = True
        make = True
    elif make == "close":
        new = False
        number.destroy()
    if type(make) == bool and new:
        if make:
            person = tk.Button(window, image=imagesforgame[number])
            person.place(x=400, y=300, anchor=tk.CENTER)
            window.after(recruits[number][3], lambda: [animate(False, number), destroything.destroyBTN(person)])
        elif not make:
            person = tk.Button(window, image=imagesforgame[number + len(recruits)])
            person.place(x=400, y=300, anchor=tk.CENTER)
            window.after(recruits[number][3], lambda: [animate(True, number), destroything.destroyBTN(person)])


def makeItems(
        **kwargs):  # name, desc, dmg, fire rate, wood/day, stone/day, metal/day, food/day, wood to make, stone, metal
    global amnt
    global delarray
    number = kwargs.get("number", None)
    person = tk.Button(window, image=imagesforgame[number])
    person.place(x=400, y=300, anchor=tk.CENTER)
    name = tk.Label(window, text=("About:" + recruits[number][0]), font=('Lucida Grande', 20))
    name.place(x=150, y=360, anchor=tk.CENTER)
    namet = tk.Label(window, text=(recruits[number][0]), font=("Courier", 44))
    namet.place(x=400, y=100, anchor=tk.CENTER)
    desc = tk.Label(window, text=recruits[number][1])
    desc.place(x=150, y=400, anchor=tk.CENTER)
    if amnt == 0:
        howmuch = tk.Scale(window, from_=1, to=100, orient=tk.HORIZONTAL, length=150, width=15, bg="grey",
                           command=lambda x: [switchamt(howmuch.get(), number)])
        howmuch.place(x=650, y=400, anchor=tk.CENTER)
        # delarray.append(howmuch)
    if amnt == 0:
        amnt = 1
    costsday = (
        "Materials/Day\n", "Wood:", str(recruits[number][4] * amnt), "  Stone:", str(recruits[number][5] * amnt),
        "\nMetal:",
        str(recruits[number][6] * amnt), "  Food:",
        str(recruits[number][7] * amnt))
    costsday = "".join(costsday)
    costsmake = (
        "Materials/Make\n", "Wood:", str(recruits[number][8] * amnt), "  Stone:", str(recruits[number][9] * amnt),
        "\nMetal:",
        str(recruits[number][10] * amnt))
    costsmake = "".join(costsmake)
    dmg = [
        "Stats\n", "Damage (higher is better):\n", str(recruits[number][2] * amnt),
        " \nReload Speed (lower is better):\n", str(recruits[number][3] * amnt)]
    dmg = "".join(dmg)
    costdisplayday = tk.Label(window, text=costsday, font=('Lucida Grande', 15))
    costdisplayday.place(x=150, y=525, anchor=tk.CENTER)
    costdisplaymake = tk.Label(window, text=costsmake, font=('Times', 15))
    costdisplaymake.place(x=150, y=460, anchor=tk.CENTER)
    damagetxt = tk.Label(window, text=dmg, font=('Times', 15))
    damagetxt.place(x=650, y=100, anchor=tk.CENTER)
    array = []
    playanim = tk.Button(window, text="Play Animation!", command=lambda: [animate("sdf", number)])
    playanim.place(x=650, y=175, anchor=tk.CENTER)
    recruitbtn = tk.Button(window, text=("Recruit! (x" + str(amnt) + ")"), width=20, height=4)
    recruitbtn.place(x=650, y=500, anchor=tk.CENTER)
    delarray.extend((person, name, desc, costdisplayday, costdisplaymake, namet, recruitbtn, damagetxt, playanim))
    if number + 1 < len(recruits):
        nexitem = tk.Button(window, text=recruits[number + 1][0])
        nexitem.place(x=525, y=250, anchor=tk.NW)
        nexxt = tk.Button(window, text=">", width=3, height=3,
                          command=lambda: [destroything.destroyBTN(arry=delarray), switchamt(0, number + 1)])
        nexxt.place(x=550, y=300, anchor=tk.CENTER)
        delarray.extend((nexxt, nexitem))
    if number - 1 >= 0:
        lastitem = tk.Button(window, text=recruits[number - 1][0])
        lastitem.place(x=275, y=250, anchor=tk.NE)
        last = tk.Button(window, text="<", width=3, height=3,
                         command=lambda: [destroything.destroyBTN(arry=delarray), switchamt(0, number - 1)])
        last.place(x=250, y=300, anchor=tk.CENTER)
        delarray.extend((last, lastitem))


def trainingCamp():
    padding = tk.Button(window, text="", width=25, height=15)
    padding.place(x=150, y=460, anchor=tk.CENTER)
    paddingt = tk.Button(window, text="", width=25, height=15)
    paddingt.place(x=650, y=460, anchor=tk.CENTER)
    paddingth = tk.Button(window, text="", width=25, height=10)
    paddingth.place(x=650, y=120, anchor=tk.CENTER)
    recroot = tk.Label(window, text="Recruit (Amount)")
    recroot.place(x=650, y=360, anchor=tk.CENTER)
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                     command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
    Home.place(x=0, y=0, anchor=tk.NW)
    makeItems(number=0)


if __name__ == "__main__":
    trainingCamp()
    window.mainloop()
