#imports
import tkinter as tk, time, random
from tkinter import messagebox
from PIL import Image, ImageTk

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

#user def functions
##home page
def home_on(event):
    pass

##next page of tutorial
def next_page(event):
    global page
    page += 1
    if page == 9:
        page = 1
    give_info()

##previous page of tutorial
def previous_page(event):
    global page
    page -= 1
    if page == 0:
        page = 8
    give_info()

##showing info on page
def give_info():
    global page, word, pagenum
    #different page means different txt file to read
    if page == 1:
        f = 'trade.txt'
    elif page == 2:
        f = 'attack.txt'
    elif page == 3:
        f = 'build.txt'
    elif page == 4:
        f = 'defend.txt'
    elif page == 5:
        f = 'city.txt'
    elif page == 6:
        f = 'retreat.txt'
    elif page == 7:
        f = 'save_load.txt'
    else:
        f = 'keyboard.txt'
    msg = ''
    #read txt file
    with open(f, 'r') as t:
        for line in t:
            msg += line
    #clear previous page
    word.destroy()
    pagenum.destroy()
    #create page
    word = tk.Label(window, text = msg, font = ('charter', 20), bg = 'cyan', fg = 'black')
    word.place(relx = 0.5, rely = 0.5, anchor = tk.CENTER)
    pagenum = tk.Label(window, text = page, font = ('charter', 20), bg = 'cyan', fg = 'black')
    pagenum.place(relx = 0.5, rely = 1, anchor = tk.S)
    
##tutorial page
def tutorial_on():
    global page, nextpage, prevpage, backtohome
    page = 1
    give_info()
    window.title('Help') #window title = Help
    window.bind('<Right>', next_page) #bind right arrow key
    window.bind('<Left>', previous_page) #bind left arrow key
    window.bind('<X>', tutorial_off) #bind x key
    nextpage.destroy()
    prevpage.destroy()
    backtohome.destroy()
    load = Image.open('/Users/langlang/images for coding/greenrightarrow.jpeg')
    load = load.resize((100, 50)) 
    render = ImageTk.PhotoImage(load)
    nextpage = tk.Button(window, image = render, width = 100, height = 50, command = lambda: [next_page(0)])
    nextpage.image = render
    nextpage.place(relx = 1, rely = 1, anchor = tk.SE)
    load = Image.open('/Users/langlang/images for coding/greenleftarrow.jpeg')
    load = load.resize((100, 50))
    render = ImageTk.PhotoImage(load)
    prevpage = tk.Button(window, image = render, width = 100, height = 50, command = lambda: [previous_page(0)])
    prevpage.image = render
    prevpage.place(relx = 0, rely = 1, anchor = tk.SW)
    backtohome = tk.Button(window, text = 'Exit', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', bg = 'red', fg = 'black', command = lambda: [home_on(0)])
    backtohome.place(relx = 0, rely = 0, anchor = tk.NW)

def tutorial_off():
    pass #TODO

##start button message box
def start_button(event):
    msg = messagebox.askyesno('', 'Have you played this game before?') #messagebox
    start_off() #destroy start page
    window.focus_force()
    if not msg: #if not played before
        tutorial_on() #create tutorial page

##create start page
def start_on():
    global word, start
    window.title('Empire Simulator') #window title = Empire Simulator
    word = tk.Label(window, text = 'Empire Simulator', font = ('charter', 60, 'italic'), bg = 'cyan', fg = 'black') #text
    word.place(relx = 0.5, rely = 0.3, anchor = tk.CENTER) #place text
    start = tk.Button(window, text = 'Start', font = ('charter', 20), width = 10, height = 3, highlightbackground = '#00FF00', bg = 'green', fg = 'black', command = lambda: [start_button(0)]) #button
    start.place(relx = 0.5, rely = 0.65, anchor = tk.CENTER) #place button
    window.bind('<Return>', start_button) #bind enter key

##destroy start page
def start_off():
    global word, start
    window.title(None)
    word.destroy()
    start.destroy()
    window.unbind('<Return>')

#actual game
if __name__ == '__main__':
    #making window
    window = tk.Tk()
    window.geometry('800x600') #window size
    window.config(bg = 'cyan') #window color
    #defining all widgets
    start = tk.Label(window, text = 'Define') #start button
    start.destroy()
    word = tk.Label(window, text = 'Define') #text for all pages
    word.destroy()
    pagenum = tk.Label(window, text = 'Define') #page number for tutorial
    pagenum.destroy()
    nextpage = tk.Label(window, text = 'Define') #page number for tutorial
    nextpage.destroy()
    prevpage = tk.Label(window, text = 'Define') #page number for tutorial
    prevpage.destroy()
    backtohome = tk.Label(window, text = 'Define') #page number for tutorial
    backtohome.destroy()
    start_on() #create start page
    window.mainloop() #mainloop
