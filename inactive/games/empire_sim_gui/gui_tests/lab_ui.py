import random
import tkinter as tk
from PIL import Image, ImageTk
from functools import partial
import platform
from tkinter import messagebox  # messagebox must be explicitly imported
# make window window
window = tk.Tk()
window.geometry("800x600")
window.title("royadle")

researched = [

]


def lab():
    Home = tk.Button(window, text="Home", width=7, height=2, highlightbackground='#FF0000', fg='#000000',
                     command=lambda: [quit(0)])  # TODO RUOYU CHANGE THIS
    Home.place(x=0, y=0, anchor=tk.NW)
    padding = tk.Button(window, text="", width=60, height=30)
    padding.place(x=300, y=300, anchor=tk.CENTER)
    scroll = tk.Scrollbar(window, orient=tk.VERTICAL)
    scroll.place(x=575, y=100, anchor=tk.CENTER)


if __name__ == "__main__":
    lab()
    window.mainloop()
