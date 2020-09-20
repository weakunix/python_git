import random
import tkinter as tk
from PIL import Image, ImageTk
import destroything

import math as albreto
import matplotlib as plt
plt.use("TkAgg")
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# make window window
window = tk.Tk()
window.geometry("800x600")
window.title("Training")

#                0     1     2        3       4          5       6           7             8          9     10
recruits = [  # name, desc, dmg, fire rate, wood/day, stone/day, metal/day, food/day, wood to make, stone, metal
    ["muscle", "Mr.I did pushups for fun...\n (no he's not on steroids)", 10, 1000, 0, 5, 0, 1, 0, 25, 0], #5 stone a day, 1 food
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


def plot(number):
    mats = [
        500,  # wood
        4000,  # rock
        2000,  # metal
        1000  # food
    ]
    color = [
        "red",
        "blue",
        "green",
        "grey"
    ]
    datapoints = []
    
    alens = []
    for ii in range(4):
        tempw = []
        matc = mats[ii] - recruits[number][8]
        if recruits[number][4 + ii] != 0:
            if ii < 3:
                alen = albreto.floor((mats[ii] - recruits[number][8+ii]) / recruits[number][4 + ii])
            else:
                alen = albreto.floor((mats[ii]) / recruits[number][4 + ii])
            for i in range(alen):
                matc -= recruits[number][4 + ii]
                tempw.append(matc)
            alens.append(alen)
        else:
            tempw = mats[ii]
        datapoints.append(tempw)
    print(datapoints)
    window.title("Graph")
    closeanim = tk.Button(window, text="Close Graph")
    closeanim.place(x=670, y=175, anchor=tk.CENTER)
    fig = Figure(figsize=(3.5, 2), dpi=100)
    a = fig.add_subplot(1, 1, 1)
    a.set_title('Materials Over Time')
    for ii in range(4):
        print(datapoints[ii])
        a.plot(datapoints[ii], color=color[ii])
    canvas = FigureCanvasTkAgg(fig, window)
    canvas.get_tk_widget().place(x=10, y=0, anchor=tk.NW)


plot(0)
window.mainloop()
