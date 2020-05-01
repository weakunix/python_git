#!/usr/local/bin/python3

import tkinter as tk
from tkinter import messagebox # messagebox must be explicitly imported

# make top window
top = tk.Tk()
top.geometry("200x200")

# button callback
def helloCallBack():
    msg = messagebox.showinfo("Hey", "Hello World!")

# place button
B = tk.Button(top, text = "Hello", command = helloCallBack)
B.place(x = 80, y = 80)

# launch main loop
top.mainloop()
