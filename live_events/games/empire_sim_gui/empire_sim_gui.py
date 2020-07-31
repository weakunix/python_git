#imports
import tkinter as tk, time, random
from tkinter import messagebox

#vars
silk = 575 #silk
mat = 550 #materials
food = 600 #food
land = 1 #land / territory
astr = 1 #army strength
ahlth = 100 #army health
wstr = 0 #wall strength
whlth = 100 #wall health
day = 0 #day
hour = '2300' #hour
city = 100 #city happiness
inpt = '' #(def) input / spare variable
deal = [] #random trade deal
savenum = 0 #save number
ehlth = 100 #enemy health
ihlth = 100 #invader health

#making window
window = tk.Tk()
window.geometry('800x600')
window.configure(bg = 'cyan')

#user def functions
##button functions

##buttons
def start_button():
    start = tk.Button(window, text = 'Start', width = 10, height = 5, bg = 'green')
    start.place(relx = 0.5, rely = 0.5, anchor = tk.CENTER)
    window.mainloop() 


#pregame stuf

start_button()

#actual game

