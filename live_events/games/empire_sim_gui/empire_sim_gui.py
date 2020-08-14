#imports
import tkinter as tk, time, random #tkinter for gui, time for pauses and timer, random for random deals
from tkinter import messagebox #message box for yes or no and information
from PIL import Image, ImageTk #Image and ImageTk for importing images

#vars
money = 100000000000 #money
cloth = 100000000000 #cloth
metal = 10000000000 #metals
food = 100000000000 #food
stone = 10000000000 #stone 
wood = 10000000000 #wood
day = 1 #day
land = 1 #land player has conquered
city = 100 #city happiness
research = [] #things that have been researched
moves = 0 #number of moves made by the player during the day (max 3 (max 5 if researched time efficiency))
support_level = 0
wall_level = 1 #wall level
wallhp = 20 #wall health
#types of walls and the image that goes with it
wall_types = {  1: ['./empire_sim_images/dirtwall.png', 'Level 1: Dirt Wall', 20],
                2: ['./empire_sim_images/stonewall.png', 'Level 2: Stone Wall', 50],
                3: ['./empire_sim_images/metalwall.png', 'Level 3: Metal Wall', 100],
                4: ['./empire_sim_images/trumpwall.png', 'Level 4: Trump Wall', 1000],
                5: ['./empire_sim_images/magicwall.png', 'Max Level: Magic "Wall"', 1234567890]   }
support_types = {   1: ['./empire_sim_images/muscle.png', 'Level 1: Stone Thrower'],
                    2: ['./empire_sim_images/slingshotty.png', 'Level 2: Slingshotter'],
                    3: ['./empire_sim_images/chushir.png', 'Level 3: Javelin Thrower'],
                    4: ['./empire_sim_images/robinhood.png', 'Level 4: Archer'],
                    5: ['./empire_sim_images/princess.png', 'Level 5: Princess'],
                    6: ['./empire_sim_images/panini.png', 'Level 6: Gun Man'],
                    7: ['./empire_sim_images/cannon.png', 'Level 7: Cannon'],
                    8: ['./empire_sim_images/albreto.png', 'Level 8: Albreto Scientist'],
                    9: ['./empire_sim_images/merlin.png', 'Max Level: Wizard']  }

#user def functions
##destroy widgets
def vanish(event, widgets):
    for i in widgets:
        i.destroy()

##unbind keys
def unstick(event, binds):
    for i in binds:
        window.unbind(i)

##upgrade wall
def upgrade_wall(event):
    #global variables
    global wall_level, wall_types, wallhp, research, money, cloth, metal, food, stone, moves, widgets
    #pre define resources player would still need to upgrade wall
    still_need = ''
    #stuff needed to upgrade depending on wall level
    if wall_level == 1:
        stuff_needed = [[money, '$', 50000], [cloth, 'Cloth', 10000], [stone, 'Stone', 25000], [food, 'Food', 10000]]
    elif wall_level == 2:
        stuff_needed = [[money, '$', 100000], [cloth, 'Cloth', 30000], [metal, 'Metal', 75000], [food, 'Food', 30000]]
    else:
        stuff_needed = [[money, '$', 1000000], [cloth, 'Cloth', 100000], [food, 'Food', 100000]]
    #if wall is level 5 tell player that their wall is at max level
    if wall_level == 5:
        msg = messagebox.showinfo(message = 'Your wall is at max level!')
    elif wall_level == 4:
        msg = messagebox.showinfo(message = 'In order to upgrade your wall you need to do the following:\n\nRepair the temple\nResearch and build a statue\nHold a ritual everyday for magic xp\nOnce you reach a certain amount of magic xp you can get special rewards and upgrades')
    #if wall level is 3
    elif wall_level == 3:
        #if player still needs more resources add those resources into still_need
        for i in stuff_needed:
            if i[0] < i[2]:
                still_need += '\n' + i[1] + ': ' + str(i[2])
        #if donald trump isn't researched then also add that to still_need
        if 'trump' not in research:
            still_need += ('\nResearch: Donald Trump (ONLY AVAILABLE AFTER DAY 50)')
        #if player has everything
        if still_need == '':
            #ask if player wants to upgrade wall
            msg = messagebox.askyesno(message = 'Do you want to spend {} {}, {} {}, and {} {} to upgrade to a level {} wall?'.format(stuff_needed[0][1], stuff_needed[0][2], stuff_needed[1][2], stuff_needed[1][1], stuff_needed[2][2], stuff_needed[2][1], wall_level + 1))
            #if response is yes
            if msg:
                #take away all needed resources
                money -= stuff_needed[0][2]
                cloth -= stuff_needed[1][2]
                food -= stuff_needed[2][2]
                wall_level += 1 #increase wall level by one
                wallhp = 1000 #wall health goes to full
                moves += 1 #add 1 move to moves
                for i in widgets: #destroy everything on wall page
                    i.destroy()
                wall_page(0) #back to wall page
        #if player still need resources
        else:
            #tell player they still need more resources
            msg = messagebox.showerror(message = 'Not enough resources!\n\nYou still need:\n' + still_need)
    #if wall level is 1 or 2
    else:
        #if player still needs more resources add those resources into still_need
        for i in stuff_needed:
            if i[0] < i[2]:
                still_need += '\n' + i[1] + ': ' + str(i[2] - i[0])
        #if player has everything
        if still_need == '':
            #ask if player wants to upgrade wall
            msg = messagebox.askyesno(message = 
'Do you want to spend {} {}, {} {}, {} {}, and {} {} to upgrade to a level {} wall?'.format(stuff_needed[0][1], stuff_needed[0][2], stuff_needed[1][2], stuff_needed[1][1], stuff_needed[2][2], stuff_needed[2][1], stuff_needed[3][2], stuff_needed[3][1], wall_level + 1))
            #if response is yes
            if msg:
                #take away all needed resources
                money -= stuff_needed[0][2]
                cloth -= stuff_needed[1][2]
                food -= stuff_needed[3][2]
                #if wall level 1 then take away stone and wall health goes to full
                if wall_level == 1:
                    stone -= stuff_needed[2][2]
                    wallhp = 50
                #else take away metal and wall health goes to full
                else:
                    metal -= stuff_needed[2][2]
                    wallhp = 100
                wall_level += 1 #increase wall level buy 1
                moves += 1 #add 1 move to moves
                for i in widgets: #destroy everything on wall page
                    i.destroy()
                wall_page(0) #back to home page
        #if player still need resources
        else:
            #tell player they still need more resources
            msg = messagebox.showerror(message = 'Not enough resources!\n\nYou still need:' + still_need)
    window.focus_force() #focus back on window after use of messageboxes

##get input for repair and heal
def get_heal(event):
    #global variables
    global heal, repair_widgets
    #getting slide input
    heal = repair_widgets[1].get()
    vanish(0, repair_widgets)
    unhide_back_to_home(0)
    repair_wall()

##unhide the back to home button
def unhide_back_to_home(event):
    global widgets
    widgets[6].place(x = 0, y = 0, anchor = tk.NW) 

##how much repair wall
def how_much_repair_wall(event):
    #global variables
    global wall_level, wall_trpes, wallhp, heal, widgets, repair_widgets
    #if wall is level 5
    if wall_level == 5:
        #tell player that level 5 wall doesn't need heal
        msg = messagebox.showinfo(message = 'Your Magic "Wall" doesn\'t need to be repaired!')
    #if wall is at full health
    elif wallhp == wall_types[wall_level][2]:
        msg = messagebox.showinfo(message = 'Your wall is at max health!') #tell player wall is at max health
    #if not at full health
    else: 
        #how much you want to heal text
        question = tk.Label(window, text = 'How much do you want to repair your wall by?', font = ('charter', 15), bg = '#00FFFF', fg = '#000000') 
        question.place(x = 645, y = 415, anchor = tk.CENTER)
        #making slider
        heal_slider = tk.Scale(window, from_ = 1, to = wall_types[wall_level][2] - wallhp, bg = '#00FFFF', fg = '#000000', orient = tk.HORIZONTAL)
        heal_slider.place(x = 645, y = 450, anchor = tk.CENTER) #entry box location
        #making heal button
        confirm_heal = tk.Button(window, text = 'Heal', highlightbackground = '#00FF00', font = ('charter', 15), width = 5, height = 1, fg = '#000000', command = lambda: get_heal(0))
        confirm_heal.place(x = 613, y = 490, anchor = tk.CENTER) 
        #cancel repair button
        cancel = tk.Button(window, text = 'Cancel', width = 5, height = 1, font = ('charter', 15), highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, repair_widgets), unstick(event, binds), unhide_back_to_home(0)]) 
        cancel.place(x = 673, y = 490, anchor = tk.CENTER)
        #hide back to home button so it doesn't cause an error
        widgets[6].place_forget()
        #repair wall widgets
        repair_widgets = [question, heal_slider, confirm_heal, cancel]
        binds = ['<Return>', '<x>']
        window.bind('<Return>', lambda event: get_heal(event)) #bind enter key to heal button 
        window.bind('<x>', lambda event: [vanish(event, repair_widgets), unstick(event, binds), unhide_back_to_home(event)]) #bind x key to cancel repair button 
    window.focus_force() #focus back on window after messageboxes

##repair wall
def repair_wall():
    #global variables
    global wall_level, wall_types, wallhp, money, cloth, metal, food, stone, moves, heal, widgets
    #resources still needed
    still_need = ''
    #stuff needed to repair depending on wall level
    if wall_level == 1:
        stuff_needed = [[money, '$', 200], [cloth, 'Cloth', 50], [food, 'Food', 50]]
    elif wall_level == 2:
        stuff_needed = [[money, '$', 500], [cloth, 'Cloth', 100], [food, 'Food', 100], [stone, 'Stone', 250]]
    elif wall_level == 3:
        stuff_needed = [[money, '$', 1000], [cloth, 'Cloth', 200], [food, 'Food', 200], [metal, 'Metal', 500]]
    else:
        stuff_needed = [[money, '$', 2500],[cloth, 'Cloth', 500], [food, 'Food', 500], [metal, 'Metal', 1000]]
    for i in stuff_needed:
        if i[0] < i[2] * heal:
            still_need += '\n' + i[1] + ': ' + str(i[2] * heal - i[0])
    #if player has all resources
    if still_need == '':
        #asking if player wants to repair (level 1 wall)
        if wall_level == 1:
            msg = messagebox.askyesno(message = 'Do you want to spend {} {}, {} {}, and {} {} to repair your wall by {}?'.format(stuff_needed[0][1], stuff_needed[0][2] * heal, stuff_needed[1][2] * heal, stuff_needed[1][1], stuff_needed[2][2] * heal, stuff_needed[2][1], heal))
        #asking if player wants to repair (other level walls)
        else: 
            msg = messagebox.askyesno(message = 'Do you want to spend {} {}, {} {}, {} {}, and {} {} to repair you wall by {}?'.format(stuff_needed[0][1], stuff_needed[0][2] * heal, stuff_needed[1][2] * heal, stuff_needed[1][1], stuff_needed[2][2] * heal, stuff_needed[2][1], stuff_needed[3][2] * heal, stuff_needed[3][1], heal))
        #if response is yes
        if msg:
            #take away resources
            money -= stuff_needed[0][2] * heal
            cloth -= stuff_needed[1][2] * heal
            food -= stuff_needed[2][2] * heal
            #if wall level is 2
            if wall_level == 2:
                stone -= stuff_needed[3][2] * heal #take away stone
            #if wall level is 3 or 4
            elif wall_level != 1:
                metal -= stuff_needed[3][2] * heal #take away metal
            #heal the wall
            wallhp += heal
            moves += 1 #add 1 move to moves
            for i in widgets: #destroy everything on wall page
                i.destroy()
            wall_page(0) #back to wall page
    #if not enough resources
    else:
        msg = messagebox.showerror(message = 'Not enough resources!\n\nYou still need:\n' + still_need) #tell player which resources are still needed
    window.focus_force()

##upgrade wall support

##wall page
def wall_page(event):
    #global variables
    global wall_level, wall_types, wallhp, money, cloth, metal, food, stone, moves, land, city, support_level, support_types, widgets
    window.title('Wall') #rename window title
    #wall image
    load = Image.open(wall_types[wall_level][0])
    load = load.resize((400, 300)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Label(window, image = render, width = 400, height = 300, bg = '#00FFFF')
    wall.image = render
    wall.place(x = 400, y = 300, anchor = tk.CENTER)
    #two wall support images
    if support_level != 0: #if wall support not 0
        load = Image.open(support_types[support_level][0])
        load = load.resize((35, 50))
        render = ImageTk.PhotoImage(load)
        support_1 = tk.Label(window, image = render, bg = '#00FFFF', width = 25, height = 40)
        support_1.image = render
        support_1.place(x = 265, y = 267, anchor = tk.SW)
        support_2 = tk.Label(window, image = render, bg = '#00FFFF', width = 25, height = 40)
        support_2.image = render
        support_2.place(x = 510, y = 235, anchor = tk.SW)
    else: #if player doesn't have wall support
        #define wall support labels so we can destroy
        support_1 = tk.Label(window, bg = '#00FFFF')
        support_1.place(x = 0, y = 0, anchor = tk.NW)
        support_2 = tk.Label(window, bg = '#00FFFF')
        support_2.place(x = 0, y = 0, anchor = tk.NW)
    #upgrade wall button
    upgrade_wall_button = tk.Button(window, text = 'Upgrade Wall', width = 10, height = 4, font = ('character', 10), fg = '#000000', command = lambda: upgrade_wall(0))
    upgrade_wall_button.place(x = 760, y = 540, anchor = tk.CENTER)
    #repair wall button
    repair = tk.Button(window, text = 'Repair Wall', width = 10, height = 4, font = ('character', 10), fg = '#000000', command = lambda: how_much_repair_wall(0))
    repair.place(x = 680, y = 540, anchor = tk.CENTER)
    #upgrade support wall button
    upgrade_support_button = tk.Button(window, text = 'Upgrade Wall Support', width = 15, height = 4, font = ('character', 10), fg = '#000000')
    upgrade_support_button.place(x = 581, y = 540, anchor = tk.CENTER)
    #back to home button
    back_to_home = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, widgets), unstick(0, binds), home_page(0)])
    back_to_home.place(x = 0, y = 0, anchor = tk.NW)
    #wall details label
    wall_details = tk.Label(window, text = wall_types[wall_level][1] + '\nWall Health: ' + str(wallhp) + ' / ' + str(wall_types[wall_level][2]), bg = '#00FFFF', font = ('charter', 30), fg = '#000000')
    wall_details.place(x = 200, y = 0, anchor = tk.NW)
    #resources text
    resources = '$: ' + str(money) + '\nCloth: ' + str(cloth) + '\nMetal: ' + str(metal) + '\nStone:' + str(stone) + '\nFood: ' + str(food) 
    #resources label
    resources = tk.Label(window, text = resources, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    resources.place(x = 800, y = 0, anchor = tk.NE)
    #widgets to destroy after wall upgrade function
    widgets = [wall, support_1, support_2, upgrade_wall_button, repair, upgrade_support_button, back_to_home, wall_details, resources]
    binds = ['<x>', '<w>', '<r>', '<s>']
    window.bind('<x>', lambda event: [vanish(event, widgets), unstick(event, binds), home_page(event)])
    window.bind('<w>', lambda event: [upgrade_wall(event)]) #bind w key
    window.bind('<r>', lambda event: [how_much_repair_wall(event)]) #bind r key

##home page
def home_page(event):
    #global variables
    global wall_level, wall_types, wallhp, research, money, cloth, metal, wood, food, stone, moves, land, city, day, support_level, support_types
    window.title('Home') #rename window title
    if 'time' not in research and moves == 3 or 'time' in research and moves == 5: #if player reaches maximum moves per day
        day += 1 #day advances
        moves = 0 #moves goes back to 0
        #taking away resources from player, if player not have enough resources, then city happiness goes down by 5
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
    #wall image button
    load = Image.open(wall_types[wall_level][0])
    load = load.resize((211, 158)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Button(window, image = render, width = 201, height = 150, command = lambda: [vanish(0, widgets), unstick(0, binds), wall_page(0)])
    wall.image = render
    wall.place(x = 800, y = 600, anchor = tk.SE)
    #two wall support images
    if support_level != 0: #if wall support not 0
        load = Image.open(support_types[support_level][0])
        load = load.resize((20, 29))
        render = ImageTk.PhotoImage(load)
        support_1 = tk.Label(window, image = render, bg = '#00FFFF', width = 10, height = 19)
        support_1.image = render
        support_1.place(x = 627, y = 505, anchor = tk.SW)
        support_2 = tk.Label(window, image = render, bg = '#00FFFF', width = 10, height = 19)
        support_2.image = render
        support_2.place(x = 757, y = 490, anchor = tk.SW)
    else: #if player doesn't have wall suppor
        #define wall support labels so we can destroy
        support_1 = tk.Label(window, bg = '#00FFFF')
        support_1.place(x = 0, y = 0, anchor = tk.NW)
        support_2 = tk.Label(window, bg = '#00FFFF')
        support_2.place(x = 0, y = 0, anchor = tk.NW)
    #player resources text
    resources = '$: ' + str(money) + '  Cloth: ' + str(cloth) + '  Metal: ' + str(metal) + '  Stone: ' + str(stone) + '  Wood: ' + str(wood) + '  Food: ' + str(food) + '\nLand: ' + str(land) + '  City Happiness: ' + str(city) + ' / 100  Day: ' + str(day) + '  Moves played: ' + str(moves) + ' / '
    #moves depending on if time efficiency has been researched
    if 'time' in research:
        resources += '5'
    else:
        resources += '3'
    #player resources label
    resources = tk.Label(window, text = resources, font = ('charter', 20), bg = '#00FFFF', fg = '#000000')
    resources.place(x = 400, y = 0, anchor = tk.N)
    widgets = [wall, support_1, support_2, resources]
    binds = ['<w>']
    window.bind('<w>', lambda event: [vanish(event, widgets), unstick(event, binds), wall_page(event)]) #bind w key to wall image button

##create start page
def start_page():
    window.title('Empire Simulator') #name window title 
    #Empire Simulator title
    start_title = tk.Label(window, text = 'Empire Simulator', font = ('charter', 60, 'italic'), bg = '#00FFFF', fg = '#000000')
    start_title.place(x = 400, y = 180, anchor = tk.CENTER) #place text
    #start button (when clicked brings you to home page and destroys start page)
    start = tk.Button(window, text = 'Start', font = ('charter', 20), width = 10, height = 3, highlightbackground = '#00FF00', bg = '#00FF00', fg = '#000000', command = lambda: [vanish(0, widgets), unstick(0, binds), home_page(0)])
    start.place(x = 400, y = 390, anchor = tk.CENTER) #place button
    widgets = [start, start_title]
    binds = ['<Return>']
    window.bind('<Return>', lambda event: [vanish(event, widgets), unstick(event, binds), home_page(event)]) #bind enter key to start button

#actual game
if __name__ == '__main__': #if main
    #making window
    window = tk.Tk()
    window.geometry('800x600') #window size
    window.config(bg = '#00FFFF') #window color
    #defining all widgets
    start_page() #create start page
    window.mainloop() #mainloop
