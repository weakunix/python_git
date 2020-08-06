#imports
import tkinter as tk, time, random #tkinter for gui, time for pauses and timer, random for random deals
from tkinter import messagebox #message box for yes or no and information
from PIL import Image, ImageTk #Image and ImageTk for importing images

#vars
money = 1000 #money
cloth = 1000 #cloth
metal = 1000 #metals
food = 1000 #food
stone = 1000 #stone 
day = 1 #day
land = 1 #land player has conquered
city = 100 #city happiness
research = [] #things that have been researched
moves = 0 #number of moves made by the player during the day (max 3 (max 5 if researched time efficiency))
wall_level = 1 #wall level
wallhp = 20 #wall health
#types of walls and the image that goes with it
wall_types = {  1: ['./images/dirtwall.png', 'Level 1 Dirt Wall', ],
                2: ['./images/stonewall.png', 'Level 2 Stone Wall'],
                3: ['./images/metalwall.png', 'Level 3 Metal Wall'],
                4: ['./images/trumpwall.png', 'Level 4 Trump Wall']}

#user def functions
##upgrade wall
def upgrade_wall(event):
    global wall_level, wall_types, research, money, cloth, metal, food, stone, moves
    '''
    globals:
    wall_level: wall level
    wall_types: types of walls and the image that goes with it
    research: things that have been researched
    money: amount of money
    cloth, metal, food, stone: resources needed for upgrade
    moves: the number of moves made by the player
    '''
    still_need = 'Not enough resources!\n\nYou still need:'
    #stuff needed to upgrade depending on wall level
    if wall_level == 1:
        stuff_needed = [[money, '$', 50000], [cloth, 'Cloth', 10000], [stone, 'Stone', 25000], [food, 'Food', 10000]]
    elif wall_level == 2:
        stuff_needed = [[money, '$', 100000], [cloth, 'Cloth', 30000], [metal, 'Metal', 75000], [food, 'Food', 30000]]
    else:
        stuff_needed = [[money, '$', 1000000], [cloth, 'Cloth', 100000], [food, 'Food', 100000]]
    if wall_level == 4:
        msg = messagebox.showinfo(message = 'Your wall is at max level!')
    elif wall_level == 3:
        for i in stuff_needed:
            if i[0] < i[2]:
                still_need += '\n' + i[1] + ': ' + str(i[2])
        if 'trump' not in research:
            still_need += ('\nResearch: Donald Trump (ONLY AVAILABLE AFTER DAY 50)')
        if still_need == 'Not enough resources!\n\nYou still need:':
            msg = messagebox.askyesno(message = 'Do you want to spend {} {}, {} {}, and {} {} to upgrade to a level {} wall?'.format(stuff_needed[0][1], stuff_needed[0][2], stuff_needed[1][2], stuff_needed[1][1], stuff_needed[2][2], stuff_needed[2][1], wall_level + 1))
            if msg:
                money -= stuff_needed[0][2]
                cloth -= stuff_needed[1][2]
                food -= stuff_needed[2][2]
                wall_level += 1
                wallhp = 1000
                moves += 1
                wall_off(0) 
        else:
            msg = messagebox.showerror(message = still_need)
    else:
        for i in stuff_needed:
            if i[0] < i[2]:
                still_need += '\n' + i[1] + ': ' + str(i[2])
        if still_need == 'Not enough resources!\n\nYou still need:':
            msg = messagebox.askyesno(message = 'Do you want to spend {} {}, {} {}, {} {}, and {} {} to upgrade to a level {} wall?'.format(stuff_needed[0][1], stuff_needed[0][2], stuff_needed[1][2], stuff_needed[1][1], stuff_needed[2][2], stuff_needed[2][1], stuff_needed[3][2], stuff_needed[3][1], wall_level + 1))
            if msg:
                money -= stuff_needed[0][2]
                cloth -= stuff_needed[1][2]
                food -= stuff_needed[3][2]
                if wall_level == 1:
                    stone -= stuff_needed[2][2]
                    wallhp = 50
                else:
                    metal -= stuff_needed[2][2]
                    wallhp = 100
                wall_level += 1
                moves += 1
                wall_off(0) 
        else:
            msg = messagebox.showerror(message = still_need)
    window.focus_force()

##wall page
def wall_on(event):
    global wall, wall_level, wall_types, wallhp, money, cloth, metal, food, stone, moves, word, wordy, land, city, clicky, clicker, clickier, clickiest, click
    '''
    globals:
    wall: wall image button
    wall_level: wall level
    wall_types: types of walls and the image that goes with it
    wallhp: wall health
    money: amount of money
    cloth, metal, food, stone: resources
    moves: the number of moves made by the player
    word: name of the wall
    wordy: shows all info of player
    land: land player conquered
    city: city happiness
    clicky: upgrade wall
    clicker: repair wall
    clickier: upgrade wall support
    clickiest: repair / heal wall support
    '''
    home_off()
    window.title('Wall')
    load = Image.open(wall_types[wall_level][0])
    load = load.resize((800, 600)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Label(window, image = render, width = 800, height = 600, bg = '#00FFFF')
    wall.image = render
    wall.place(relx = 0, rely = 0, anchor = tk.NW) 
    clicky = tk.Button(window, text = 'Upgrade Wall', width = 10, height = 4, font = ('character', 10), fg = '#000000', command = lambda: upgrade_wall(0))
    clicky.place(relx = 0.95, rely = 0.9, anchor = tk.CENTER)
    clicker = tk.Button(window, text = 'Repair Wall', width = 10, height = 4, font = ('character', 10), fg = '#000000')
    clicker.place(relx = 0.85, rely = 0.9, anchor = tk.CENTER)
    clickier = tk.Button(window, text = 'Upgrade Wall Support', width = 15, height = 4, font = ('character', 10), fg = '#000000')
    clickier.place(relx = 0.727, rely = 0.9, anchor = tk.CENTER)
    clickiest = tk.Button(window, text = 'Repair / Heal Wall Support', width = 20, height = 4, font = ('character', 10), fg = '#000000')
    clickiest.place(relx = 0.562, rely = 0.9, anchor = tk.CENTER)
    click = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', fg = '#000000', command = lambda: wall_off(0))
    click.place(relx = 0, rely = 0, anchor = tk.NW)
    word = tk.Label(window, text = wall_types[wall_level][1], bg = '#00FFFF', font = ('charter', 40), fg = '#000000')
    word.place(relx = 0.25, rely = 0, anchor = tk.NW)
    wordy = '$: ' + str(money) + '\nCloth: ' + str(cloth) + '\nMetal: ' + str(metal) + '\nStone:' + str(stone) + '\nFood: ' + str(food)
    wordy = tk.Label(window, text = wordy, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    wordy.place(relx = 1, rely = 0, anchor = tk.NE)
    window.bind('<x>', lambda event: wall_off(event)) #bind x key
    window.bind('<w>', lambda event: upgrade_wall(event)) #bind w key

##destroy wall page
def wall_off(event):
    global wall, clicky, clicker, clickier, clickiest, click, word, wordy
    '''
    globals:
    wall: wall image
    clicky: upgrade wall
    clicker: repair wall
    clickier: upgrade wall support
    clickiest: repair / heal  wall support
    click: back to home
    word: type of wall text
    wordy: shows all player info
    '''
    window.title(None) #unset title
    #destroy
    wall.destroy()
    clicky.destroy()
    click.destroy()
    clicker.destroy()
    clickier.destroy()
    clickiest.destroy()
    click.destroy()
    word.destroy()
    wordy.destroy()
    #unbind
    window.unbind('<x>')
    home_on()

##home page
def home_on():
    global wall, wall_level, wall_types, wallhp, money, cloth, metal, food, stone, moves, word, land, city
    '''
    globals:
    wall: wall image button
    wall_level: wall level
    wall_types: types of walls and the image that goes with it
    wallhp: wall health
    money: amount of money
    cloth, metal, food, stone: resources
    moves: the number of moves made by the player
    word: shows all info of player
    land: land player conquered
    city: city happiness
    '''
    if moves == 3:
        day += 1
        moves = 0
        if food >= land * 20:
            food -= land * 20
        else:
            food = 0
            city -= 5
        if cloth >= land * 10:
            food -= land * 10
        else:
            cloth = 0
            city -= 5
    window.title('Home') #rename window title
    #wall image button
    load = Image.open(wall_types[wall_level][0])
    load = load.resize((400, 300)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Button(window, image = render, width = 375, height = 275, command = lambda: wall_on(0)) 
    wall.image = render
    wall.place(relx = 0.7, rely = 0.7, anchor = tk.CENTER)
    word = '$: ' + str(money) + '\nCloth: ' + str(cloth) + '\nMetal: ' + str(metal) + '\nStone:' + str(stone) + '\nFood: ' + str(food) + '\nLand: ' + str(land) + '\nCity Happiness: ' + str(city) + ' / 100\nMoves played: ' + str(moves) + ' / '
    if 'time' in research:
        word += '5'
    else:
        word += '3'
    word = tk.Label(window, text = word, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    word.place(relx = 1, rely = 0, anchor = tk.NE)
    window.bind('<w>', lambda event: wall_on(event)) #bind w key

##destroy home page
def home_off():
    global wall, word
    '''
    globals:
    wall: wall image button
    word: shows all player info
    '''
    window.title(None) #unset title
    #clear page
    wall.destroy()
    word.destroy()

##next page of tutorial
def next_page(event):
    global page
    '''
    globals:
    page: page you are on for tutorial
    '''
    page += 1 #page goes up by one
    if page == 9: #if goes over 8 resets to page 1
        page = 1
    give_info() #give info function

##previous page of tutorial
def previous_page(event):
    global page
    '''
    globals:
    page: page you are on for tutorial
    '''
    page -= 1 #page goes down by one
    if page == 0: #if goes under 1 resets to page 8
        page = 8
    give_info() #give info function

##showing info on page
def give_info():
    global page, word, wordy 
    '''
    globals:
    page: page you are on for tutorial
    word: tutorial text
    wordy: page number
    '''
    #dictionary of all the txt files that need to be read depending on page
    allhelp = { 1: 'trade.txt',
                2: 'attack.txt',
                3: 'build.txt',
                4: 'defend.txt',
                5: 'city.txt',
                6: 'retreat.txt',
                7: 'save_load.txt',
                8: 'keyboard.txt'}
    f = allhelp[page] #txt file depending on page
    msg = ''
    #read txt file
    with open(f, 'r') as t:
        for line in t:
            msg += line
    #clear previous page
    word.destroy()
    wordy.destroy()
    #create page
    word = tk.Label(window, text = msg, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    word.place(relx = 0.5, rely = 0.5, anchor = tk.CENTER)
    wordy = tk.Label(window, text = page, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    wordy.place(relx = 0.5, rely = 1, anchor = tk.S)
    
##tutorial page
def tutorial_on():
    global page, click, clicker, clicky
    '''
    globals:
    page: page you are on for tutorial
    click: back to home button
    clicker: previous page button
    clicky: next page button
    '''
    page = 1 #page set to 1
    give_info() #give info function to display text
    window.title('Help') #rename window title
    window.bind('<Right>', lambda event: next_page(event)) #bind right arrow key
    window.bind('<Left>', lambda event: previous_page(event)) #bind left arrow key
    window.bind('<x>', lambda event: tutorial_off(event)) #bind x key
    #clear
    clicky.destroy()
    clicker.destroy()
    click.destroy()
    #next page button
    load = Image.open('./images/greenrightarrow.png')
    load = load.resize((100, 50))
    render = ImageTk.PhotoImage(load)
    clicky = tk.Button(window, image = render, width = 80, height = 30, command = lambda: next_page(0))
    clicky.image = render
    clicky.place(relx = 0.975, rely = 0.975, anchor = tk.SE)
    #previous page button
    load = Image.open('./images/greenleftarrow.png')
    load = load.resize((100, 50))
    render = ImageTk.PhotoImage(load)
    clicker = tk.Button(window, image = render, width = 80, height = 30, command = lambda: previous_page(0))
    clicker.image = render
    clicker.place(relx = 0.025, rely = 0.975, anchor = tk.SW)
    #back to home button
    click = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', bg = '#FF0000', fg = '#000000', command = lambda: tutorial_off(0))
    click.place(relx = 0, rely = 0, anchor = tk.NW)

def tutorial_off(event):
    global click, clicker, clicky, word, wordy
    '''
    globals:
    click: back to home button
    clicker: previous page button
    clicky: next page button
    word: tutorial text
    wordy: page number
    '''
    window.title(None) #unset window title
    clicky.destroy() #destroy
    clicker.destroy()
    click.destroy()
    word.destroy()
    wordy.destroy()
    window.unbind('<Right>') #unbind
    window.unbind('<Left>')
    window.unbind('<x>')
    home_on() #home page

##start button message box
def start_button(event):
    msg = messagebox.askyesno(message = 'Have you played this game before?') #messagebox
    start_off() #destroy start page
    window.focus_force() #focus back onto window
    if not msg: #if not played before
        tutorial_on() #create tutorial page
    else:
        home_on() #home page

##create start page
def start_on():
    global click, word
    '''
    globals:
    click: start button
    word: Empire Simulator title
    '''
    window.title('Empire Simulator') #name window title 
    #Empire Simulator title
    word = tk.Label(window, text = 'Empire Simulator', font = ('charter', 60, 'italic'), bg = '#00FFFF', fg = '#000000')
    word.place(relx = 0.5, rely = 0.3, anchor = tk.CENTER) #place text
    #start button
    click = tk.Button(window, text = 'Start', font = ('charter', 20), width = 10, height = 3, highlightbackground = '#00FF00', bg = '#00FF00', fg = '#000000', command = lambda: start_button(0)) 
    click.place(relx = 0.5, rely = 0.65, anchor = tk.CENTER) #place button
    window.bind('<Return>', lambda event: start_button(event)) #bind enter key

##destroy start page
def start_off():
    global click, word
    '''
    globals:
    click: start button
    word: Empire Simulator title
    '''
    window.title(None) #unset window title
    #clear page
    word.destroy()
    click.destroy()
    window.unbind('<Return>') #unbind enter key

#actual game
if __name__ == '__main__': #if main
    #making window
    window = tk.Tk()
    window.geometry('800x600') #window size
    window.config(bg = '#00FFFF') #window color
    #defining all widgets
    click = tk.Label(window, text = 'Define')
    click.destroy()
    clicky = tk.Label(window, text = 'Define')
    clicky.destroy()
    clicker = tk.Label(window, text = 'Define') 
    clicker.destroy()
    clickier = tk.Label(window, text = 'Define') 
    clickier.destroy()
    clickiest = tk.Label(window, text = 'Define') 
    clickiest.destroy()
    word = tk.Label(window, text = 'Define')
    word.destroy()
    wordy = tk.Label(window, text = 'Define')
    wordy.destroy()
    wall = tk.Label(window, text = 'Define') #wall image button
    wall.destroy()
    start_on() #create start page
    window.mainloop() #mainloop
