import tkinter as tk
from tkinter import messagebox  # messagebox must be explicitly imported

# make window window
window = tk.Tk()
window.geometry("800x600")
window.title("royadle")

# variables
solddata = [  # example of what sold in format
    ["Cowland", "Materials", 1000, 10],  # castle from, what sold, how many, money per
    ["Eagle Claw Nation", "Food", 10, 10],  # castle from, what sold, how many, money per
    [False, "Magic Fragment", 1, 1000]  # no castle (wandering trader), selling magic fragment(1) for (1000)
]


# button destroy
def destroybtn(*destroys):
    for args in destroys:
        args.destroy()


# place button
def pageo():
    whereToPlace = [
        [200, 75],
        [400, 75],
        [200, 300],
        [400, 300]
    ]
    offersText = tk.Label(window, text="Offers:")
    offersText.config(font=("Courier", 44))
    offersText.place(x=400, y=25, anchor=tk.CENTER)
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000')
    Home.place(x=0, y=0, anchor=tk.NW)
    nexxt = tk.Button(window, text=">",  # make load button
                      command=lambda: [paget(), destroybtn(nexxt, Home)])
    nexxt.place(x=500, y=550, anchor=tk.CENTER)
    for i in range(len(solddata)):
        offer = tk.Button(window, text="", width=20, height=12)
        offer.place(x=whereToPlace[i][0], y=whereToPlace[i][1])


def paget():
    last = tk.Button(window, text="<",  # make delete save button
                     command=lambda: [pageo(), destroybtn(last)])
    last.place(x=300, y=550, anchor=tk.CENTER)


# launch main loop
if __name__ == "__main__":
    pageo()
    window.mainloop()
