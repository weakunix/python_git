from PIL import Image, ImageTk
import tkinter as tk
window = tk.Tk()
window.geometry("800x600")
load = Image.open("titleeee.png")
render = ImageTk.PhotoImage(load)
img = tk.Label(window, image = render)
img.image = render
img.place(x=200,y=200)
window.mainloop()
