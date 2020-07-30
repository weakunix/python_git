import tkinter as tk
from tkinter import messagebox # messagebox must be explicitly imported

# make top window
top = tk.Tk()
top.geometry("200x200")

# button callback

# place button
B = tk.Button(top, text = "SinglePlayer")
B.place(x = 80, y = 80)
D = tk.Button(top, text = "MultiPlayer")
D.place(x = 160, y = 80)

# launch main loop
top.mainloop()
