#imports
import tkinter as tk, time, random #tkinter for gui, time for pauses and timer, random for random deals
from tkinter import messagebox #message box for yes or no and information
from PIL import Image, ImageTk #Image and ImageTk for importing images
from tkinter import ttk

#vars
materials = [1000000000, 1000000000, 1000000000, 1000000000, 1000000000] #materials in the format [money, food, stone, metal, wood]
day = 1 #day
land = 1 #land player has conquered
happy = 100 #happy happiness
research = [] #things that have been researched
moves = 0 #number of moves made by the player during the day (max 3 (max 5 if researched time efficiency))
levels = [0, 1, 20, 1, 1, 1, 1] #levels and health of things in the format [wall support level, wall level, wall health, training camp level, research lab level, district level, market level]
#types of walls
wall_types = {  1: ['./empire_sim_images/dirtwall.png', 'Level 1: Dirt Wall', 20],
                2: ['./empire_sim_images/stonewall.png', 'Level 2: Stone Wall', 50],
                3: ['./empire_sim_images/metalwall.png', 'Level 3: Metal Wall', 100],
                4: ['./empire_sim_images/trumpwall.png', 'Level 4: Trump Wall', 1000],
                5: ['./empire_sim_images/magicwall.png', 'Max Level: Magic "Wall"', 'Infinite'] }
#support types
support_types = {   1: ['./empire_sim_images/muscle.png', 'Level 1: Stone Thrower'],
                    2: ['./empire_sim_images/slingshotty.png', 'Level 2: Slingshotter'],
                    3: ['./empire_sim_images/chushir.png', 'Level 3: Javelin Thrower'],
                    4: ['./empire_sim_images/robinhood.png', 'Level 4: Archer'],
                    5: ['./empire_sim_images/princess.png', 'Level 5: Princess'],
                    6: ['./empire_sim_images/panini.png', 'Level 6: Sniper'],
                    7: ['./empire_sim_images/cannon.png', 'Level 7: Cannon'],
                    8: ['./empire_sim_images/albreto.png', 'Level 8: Albreto Scientist'],
                    9: ['./empire_sim_images/merlin.png', 'Max Level: Wizard']  }
#training camp types
training_types = {  1: './empire_sim_images/stonecamp',
                    2: './empire_sim_images/arrowcamp',
                    3: './empire_sim_images/cannoncamp',
                    4: './empire_sim_images/albretocamp'    }
#research lab types
lab_types = {   1: './empire_sim_images/stonelab.png',
                2: './empire_sim_images/albretolab.png' }
#district types
district_types = {  1: './empire_sim_images/tents.png',
                    2: './empire_sim_images/stonebuilding.png',
                    3: './empire_sim_images/modernbuilding.png'  }
#market types
market_types = {    1: './empire_sim_images/stonemarket.png',
                    2: './empire_sim_images/supermarket.png',
                    3: './empire_sim_images/stalkmarket.png'    }

#classes
##class page
class Page:
    #init
    def __init__(self):
        self.widgets = []
        self.binds = []
    #clear page
    def clear(self, **kwargs):
        for i in self.widgets:
            i.destroy()
        for i in self.binds:
            window.unbind(i) 

#functions
##start page
def StartPage():
    #start page
    start_page = Page()
    #create start page method
    window.title('Empire Simulator') #name window title 
    window.config(bg = '#00FFFF') #window color
    #Empire Simulator title
    start_title = tk.Label(window, text = 'Empire Simulator', font = ('charter', 60, 'italic'), bg = '#00FFFF', fg = '#000000')
    start_title.place(x = 400, y = 180, anchor = tk.CENTER) 
    #start button
    start = tk.Button(window, text = 'Start', font = ('charter', 20), width = 10, height = 3, highlightbackground = '#00FF00', bg = '#00FF00', fg = '#000000', command = lambda: [start_page.clear(), HomePage()])
    start.place(x = 400, y = 390, anchor = tk.CENTER) 
    window.bind('<Return>', lambda event: [start_page.clear(), HomePage()]) #bind enter key to start button
    start_page.widgets = [start, start_title] #widgets
    start_page.binds = ['<Return>'] #binds
        
def HomePage():
    #home page
    home_page = Page()
    window.title('Home') #rename window title
    window.config(bg = '#00FF00') #window color
    #globals
    global materials, day, land, happy, research, moves, levels, wall_types, support_types, training_types, lab_types, district_types, market_types
    if 'time' not in research and moves == 3 or 'time' in research and moves == 5: #if player reaches maximum moves per day
        day += 1 #day advances
        moves = 0 #moves goes back to 0
        #taking away food from player, if player not have enough resources, then city happiness goes down by 5
        if materials[1] >= land * 20:
            materials[1] -= land * 20
        else:
            materials[1] = 0
            happy -= 5
    #wall image button
    load = Image.open(wall_types[levels[1]][0])
    load = load.resize((422, 316)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Button(window, image = render, width = 402, height = 300, command = lambda: [vanish(0, widgets), unstick(0, binds), wall_page(0)])
    wall.image = render
    wall.place(x = 800, y = 600, anchor = tk.SE)
    #training camp button
    load = Image.open(training_types[levels[3]] + '.png')
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    training = tk.Button(window, image = render, width = 201, height = 140, command = lambda: [vanish(0, widgets), unstick(0, binds), training_page(0)])
    training.image = render
    training.place(x = 625, y = 300, anchor = tk.CENTER)
    #market button
    load = Image.open(market_types[levels[6]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    market = tk.Button(window, image = render, width = 186, height = 145)
    market.image = render
    market.place(x = 350, y = 350, anchor = tk.CENTER)
    #research lab button
    load = Image.open(lab_types[levels[4]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    lab = tk.Button(window, image = render, width = 191, height = 120)
    lab.image = render
    lab.place(x = 450, y = 200, anchor = tk.CENTER)
    #district button
    load = Image.open(district_types[levels[5]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    district = tk.Button(window, image = render, width = 191, height = 150)
    district.image = render
    district.place(x = 0, y = 600, anchor = tk.SW)
    #two wall support images
    if levels[0] != 0: #if wall support not 0
        load = Image.open(support_types[levels[0]][0])
        load = load.resize((20, 29))
        render = ImageTk.PhotoImage(load)
        support_1 = tk.Label(window, image = render, bg = '#00FF00', width = 10, height = 19)
        support_1.image = render
        support_1.place(x = 627, y = 505, anchor = tk.SW)
        support_2 = tk.Label(window, image = render, bg = '#00FF00', width = 10, height = 19)
        support_2.image = render
        if levels[1] == 2 or levels[1] == 3:
            support_2.place(x = 760, y = 485, anchor = tk.SW)
        else:
            support_2.place(x = 757, y = 490, anchor = tk.SW)
    #player stats text
    stats = '$: ' + str(materials[0]) + '  Food: ' + str(materials[1]) + '  Stone: ' + str(materials[2]) + '  Metal: ' + str(materials[3]) + '  Wood: ' + str(materials[4]) + '\nLand: ' + str(land) + '  City Happiness: ' + str(happy) + ' / 100  Day: ' + str(day) + '  Moves played: ' + str(moves) + ' / '
    #moves depending on if time efficiency has been researched
    if 'time' in research:
        stats += '5'
    else:
        stats += '3'
    #player resources label
    stats = tk.Label(window, text = stats, font = ('charter', 20), bg = '#00FF00', fg = '#000000')
    stats.place(x = 400, y = 0, anchor = tk.N)
    widgets = [wall, stats, training, district, lab, market]
    #if player has wall supports add those to widgets
    if levels[0] != 0:
        widgets.append(support_1)
        widgets.append(support_2)
    binds = ['<w>', '<t>']
    window.bind('<w>', lambda event: [vanish(event, widgets), unstick(event, binds), wall_page(event)]) #bind w key to wall image button
    window.bind('<t>', lambda event: [vanish(event, widgets), unstick(event, binds), training_page(event)]) #bind w key to training camp image button
  
#actual game
if __name__ == '__main__': #if main
    #making window
    window = tk.Tk()
    window.geometry('800x600') #window size
    StartPage() #create start page
    window.mainloop() #mainloop









'''
#vars
materials = [1000000000, 1000000000, 1000000000, 1000000000, 1000000000] #materials in the format [money, food, stone, metal, wood]
day = 1 #day
land = 1 #land player has conquered
happy = 100 #happy happiness
research = [] #things that have been researched
moves = 0 #number of moves made by the player during the day (max 3 (max 5 if researched time efficiency))
levels = [0, 1, 20, 1, 1, 1, 1] #levels and health of things in the format [wall support level, wall level, wall health, training camp level, research lab level, district level, market level]
#types of walls
wall_types = {  1: ['./empire_sim_images/dirtwall.png', 'Level 1: Dirt Wall', 20],
                2: ['./empire_sim_images/stonewall.png', 'Level 2: Stone Wall', 50],
                3: ['./empire_sim_images/metalwall.png', 'Level 3: Metal Wall', 100],
                4: ['./empire_sim_images/trumpwall.png', 'Level 4: Trump Wall', 1000],
                5: ['./empire_sim_images/magicwall.png', 'Max Level: Magic "Wall"', 'Infinite'] }
#support types
support_types = {   1: ['./empire_sim_images/muscle.png', 'Level 1: Stone Thrower'],
                    2: ['./empire_sim_images/slingshotty.png', 'Level 2: Slingshotter'],
                    3: ['./empire_sim_images/chushir.png', 'Level 3: Javelin Thrower'],
                    4: ['./empire_sim_images/robinhood.png', 'Level 4: Archer'],
                    5: ['./empire_sim_images/princess.png', 'Level 5: Princess'],
                    6: ['./empire_sim_images/panini.png', 'Level 6: Sniper'],
                    7: ['./empire_sim_images/cannon.png', 'Level 7: Cannon'],
                    8: ['./empire_sim_images/albreto.png', 'Level 8: Albreto Scientist'],
                    9: ['./empire_sim_images/merlin.png', 'Max Level: Wizard']  }
#training camp types
training_types = {  1: './empire_sim_images/stonecamp',
                    2: './empire_sim_images/arrowcamp',
                    3: './empire_sim_images/cannoncamp',
                    4: './empire_sim_images/albretocamp'    }
#research lab types
lab_types = {   1: './empire_sim_images/stonelab.png',
                2: './empire_sim_images/albretolab.png' }
#district types
district_types = {  1: './empire_sim_images/tents.png',
                    2: './empire_sim_images/stonebuilding.png',
                    3: './empire_sim_images/modernbuilding.png'  }
#market types
market_types = {    1: './empire_sim_images/stonemarket.png',
                    2: './empire_sim_images/supermarket.png',
                    3: './empire_sim_images/stalkmarket.png'    }

#user def functions
##destroy widgets
def vanish(event, widgets):
    for i in widgets:
        i.destroy()

##unbind keys
def unstick(event, binds):
    for i in binds:
        window.unbind(i)

##get input for repair and heal
def get_heal(event):
    #global variables
    global heal, repair_widgets
    #getting slide input
    heal = repair_widgets[1].get()
    vanish(0, repair_widgets)
    unhide_buttons(0)
    upgrade(0, 2)

##unhide all of the buttons
def unhide_buttons(event):
    global widgets, binds
    #upgrade wall button
    upgrade_wall_button = tk.Button(window, text = 'Upgrade Wall', width = 10, height = 4, font = ('charter', 10), fg = '#000000', command = lambda: upgrade_wall(1, 0))
    upgrade_wall_button.place(x = 760, y = 540, anchor = tk.CENTER)
    #repair wall button
    repair = tk.Button(window, text = 'Repair Wall', width = 10, height = 4, font = ('charter', 10), fg = '#000000', command = lambda: how_much_repair_wall(0))
    repair.place(x = 680, y = 540, anchor = tk.CENTER)
    #upgrade support wall button
    upgrade_support_button = tk.Button(window, text = 'Upgrade Wall Support', width = 15, height = 4, font = ('charter', 10), fg = '#000000', command = lambda: [upgrade(0, 0)])
    upgrade_support_button.place(x = 581, y = 540, anchor = tk.CENTER)
    #back to home button
    back_to_home = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, widgets), unstick(0, binds), home_page(0)])
    back_to_home.place(x = 0, y = 0, anchor = tk.NW)
    #rebind x key
    window.bind('<x>', lambda event: [vanish(event, widgets), unstick(event, binds), home_page(event)])
    #add buttons back to widgets
    widgets += [upgrade_wall_button, repair, upgrade_support_button, back_to_home]

##how much repair wall
def how_much_repair_wall(event):
    #global variables
    global levels, wall_types, heal, widgets, repair_widgets
    #if wall is level 5
    if levels[1] == 5:
        #tell player that level 5 wall doesn't need heal
        msg = messagebox.showinfo(message = 'Your Magic "Wall" doesn\'t need to be repaired!')
    #if wall is at full health
    elif levels[2] == wall_types[levels[1]][2]:
        msg = messagebox.showinfo(message = 'Your wall is at max health!') #tell player wall is at max health
    #if not at full health
    else: 
        #how much you want to heal text
        question = tk.Label(window, text = 'How much do you want to repair your wall by?', font = ('charter', 15), bg = '#00FF00', fg = '#000000') 
        question.place(x = 645, y = 415, anchor = tk.CENTER)
        #making slider
        heal_slider = tk.Scale(window, from_ = 1, to = wall_types[levels[1]][2] - levels[2], bg = '#00FF00', fg = '#000000', orient = tk.HORIZONTAL)
        heal_slider.place(x = 645, y = 450, anchor = tk.CENTER) #entry box location
        #making heal button
        confirm_heal = tk.Button(window, text = 'Heal', highlightbackground = '#00FF00', font = ('charter', 15), width = 5, height = 1, fg = '#000000', command = lambda: get_heal(0))
        confirm_heal.place(x = 613, y = 490, anchor = tk.CENTER) 
        #cancel repair button
        cancel = tk.Button(window, text = 'Cancel', width = 5, height = 1, font = ('charter', 15), highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, repair_widgets), unstick(event, binds), unhide_buttons(0)]) 
        cancel.place(x = 673, y = 490, anchor = tk.CENTER)
        #hide all buttons so there is no error 
        for i in range(3, 7):
            widgets[i].destroy()
        #repair wall widgets
        repair_widgets = [question, heal_slider, confirm_heal, cancel]
        binds = ['<Return>', '<x>']
        window.bind('<Return>', lambda event: get_heal(event)) #bind enter key to heal button 
        window.bind('<x>', lambda event: [vanish(event, repair_widgets), unstick(event, binds), unhide_buttons(event)]) #bind x key to cancel repair button 
    window.focus_force() #focus back on window after messageboxes

##upgrade / heal
def upgrade(event, upgrading): 
    #global variables
    global wall_types, levels, support_types, research, materials, moves, widgets, heal
    #needed materials for upgrade in the format [money, food, stone, metal, wood, research] and for each material in the format [upgrade wall support, upgrade wall, repair wall]
    need_materials = {      0: [[5000, 0, 0], [5000, 0, 0], [15000, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]],
                            1: [[50000, 50000, 200], [10000, 10000, 50], [25000, 25000, 0], [0, 0, 0], [0, 0, 0], [[['slingshot', 'Research: Slingshot']], 0, 0]],
                            2: [[75000, 100000, 500], [25000, 25000, 100], [0, 0, 250], [25000, 100000, 0], [50000, 0, 0], [[['javelin', 'Research: Javelin'], ['Level 2: Stone Wall', 'Upgrade: Level 2 Stone Wall']], 0, 0]],
                            3: [[100000, 500000, 1000], [50000, 100000, 250], [0, 0, 0], [50000, 250000, 500], [75000, 0, 0], [[['bow', 'Research: Bow']], [['trump', 'Research: Donald Trump']], 0]],
                            4: [[250000, 0, 2500], [100000, 0, 500], [0, 0, 0], [100000, 0, 1000], [150000, 0, 0], [[['flaming arrows', 'Research: Flaming Arrows']], [['temple', 'Control: Temple for 10 days']], 0]],
                            5: [[750000, 0, 0], [250000, 0, 0], [0, 0, 0], [500000, 0, 0], [0, 0, 0], [[['sniper', 'Research: Sniper'], ['Level 3: Metal Wall', 'Upgrade: Level 3 Metal Wall']], 0, 0]],
                            6: [[1250000, 0, 0], [500000, 0, 0], [0, 0, 0], [1000000, 0, 0], [0, 0, 0], [[['cannon', 'Research: Cannon']], 0, 0]],
                            7: [[2500000, 0, 0], [1500000, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [[['albreto', 'Research: Albreto Science Flask'], ['Level 4: Trump Wall', 'Upgrade: Level 4 Trump Wall']], 0, 0]],
                            8: [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [[['temple', 'Control: Temple for 10 days']], 0, 0]]   }
    #names of materials
    material_names = {  0: '$: ',
                        1: 'Food: ',
                        2: 'Stone: ',
                        3: 'Metal: ',
                        4: 'Wood: ' }
    #what you are upgrading in words and the action (upgrade, heal, repair) 
    upgrading_names = { 0: ['wall support', 'upgrade'],
                        1: ['wall', 'upgrade'],
                        2: ['wall', 'repair']   }
    #level of the thing player is upgrading, repairing, or healing (neccessary because it is a DIFFERENT list than levels)
    upgrading_level = { 0: levels[0],
                        1: levels[1],
                        2: levels[1]    }
    #setting heal if not repairing
    if upgrading_names[upgrading][1] == 'upgrade':
        heal = 1
    #if upgrade / heal cannot occur because at max level / health tell player
    #upgrade wall support
    if upgrading == 0 and levels[0] == 9:
        msg = messagebox.showinfo(message = 'Your wall support is at max level!')
    #upgrade wall
    elif upgrading == 1 and levels[1] == 5:
        msg = messagebox.showinfo(message = 'Your wall is at max level!')
    #repair wall (magic wall)
    elif upgrading == 2 and levels[1] == 5:
        msg = messagebox.showinfo(message = 'The Magic "Wall" doesn\'t need to be repaired!')
    #repair wall (other walls)
    elif upgrading == 2 and levels[2] == wall_types[levels[1]][2]:
        msg = messagebox.showinfo(message = 'Your wall is at max health!')
    #else continue with upgrade / heal
    else:
        still_need = '' #resources still needed
        for i in range(5):
            #checking for each material if player has enough
            if materials[i] < heal * need_materials[upgrading_level[upgrading]][i][upgrading]:
                still_need += '\n' + material_names[i] + str(heal * need_materials[upgrading_level[upgrading]][i][upgrading] - materials[i])
        #check for researches
        if need_materials[upgrading_level[upgrading]][-1][upgrading] != 0:
            for i in need_materials[upgrading_level[upgrading]][-1][upgrading]:
                if i[0] not in research:
                    still_need += '\n' + i[1]
        #has all needed materials and researches
        if still_need == '':
            #asking player if the want to upgrade / heal
            msg = 'Do you want to spend:\n'
            #listing out each material
            for i in range(5):
                if need_materials[upgrading_level[upgrading]][i][upgrading] != 0:
                    msg += '\n' + material_names[i] + str(heal * need_materials[upgrading_level[upgrading]][i][upgrading])
            #formatting the question to fit upgrade, repair, or heal
            if upgrading_names[1] == 'upgrade':
                msg += '\n\nTo upgrade to a level {} {}?'.format(levels[upgrading] + 1, upgrading_names[upgrading][0])
            else:
                msg += '\n\nTo {} your {} by {}?'.format(upgrading_names[upgrading][1], upgrading_names[upgrading][0], heal)
            msg = messagebox.askyesno(message = msg)
            #if answer is yes
            if msg:
                #taking away resources
                for i in range(5):
                    materials[i] -= heal * need_materials[upgrading_level[upgrading]][i][upgrading]
                #heal or adding 1 to a thing to upgrade
                levels[upgrading] += heal
                #if upgrading wall set the wall health to max
                if upgrading == 1:
                    levels[2] = wall_types[levels[1]][2]
                    research.append(wall_types[levels[1]][1])
                for i in widgets: #destroy everything on wall page
                    i.destroy()
                wall_page(0) #back to wall page

        #doesn't have all needed materials and researches
        else:
            msg = messagebox.showerror(message = 'Not enough resources!\n\nYou still need:' + still_need)
    window.focus_force() #focus back on window after use of messageboxes

##wall page
def wall_page(event):
    #global variables
    global wall_types, materials, moves, land, happy, levels, support_types, widgets, binds
    window.title('Wall') #rename window title
    #wall image
    load = Image.open(wall_types[levels[1]][0])
    load = load.resize((400, 300)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Label(window, image = render, width = 400, height = 300, bg = '#00FF00')
    wall.image = render
    wall.place(x = 400, y = 300, anchor = tk.CENTER)
    #two wall support images
    if levels[0] != 0: #if wall support not 0
        load = Image.open(support_types[levels[0]][0])
        load = load.resize((35, 50))
        render = ImageTk.PhotoImage(load)
        support_1 = tk.Label(window, image = render, bg = '#00FF00', width = 25, height = 40)
        support_1.image = render
        support_1.place(x = 265, y = 267, anchor = tk.SW)
        support_2 = tk.Label(window, image = render, bg = '#00FF00', width = 25, height = 40)
        support_2.image = render
        if levels[1] == 2 or levels[1] == 3:
            support_2.place(x = 515, y = 225, anchor = tk.SW)
        else:
            support_2.place(x = 510, y = 235, anchor = tk.SW)
    #upgrade wall button
    upgrade_wall_button = tk.Button(window, text = 'Upgrade Wall', height = 4, font = ('charter', 10), fg = '#000000', command = lambda: [upgrade(0, 1)])
    upgrade_wall_button.place(x = 760, y = 540, anchor = tk.CENTER)
    #repair wall button
    repair = tk.Button(window, text = 'Repair Wall', height = 4, font = ('charter', 10), fg = '#000000', command = lambda: how_much_repair_wall(0))
    repair.place(x = 680, y = 540, anchor = tk.CENTER)
    #upgrade wall support button
    upgrade_support_button = tk.Button(window, text = 'Upgrade Wall Support', height = 4, font = ('charter', 10), fg = '#000000', command = lambda: [upgrade(0, 0)])
    upgrade_support_button.place(x = 581, y = 540, anchor = tk.CENTER)
    #back to home button
    back_to_home = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, widgets), unstick(0, binds), home_page(0)])
    back_to_home.place(x = 0, y = 0, anchor = tk.NW)
    #wall details label
    wall_details = tk.Label(window, text = wall_types[levels[1]][1] + '\nWall Health: ' + str(levels[2]) + ' / ' + str(wall_types[levels[1]][2]), bg = '#00FF00', font = ('charter', 30), fg = '#000000')
    wall_details.place(x = 200, y = 0, anchor = tk.NW)
    #stats text
    stats = '$: ' + str(materials[0])  + '\nFood: ' + str(materials[1]) + '\nStone:' + str(materials[2]) + '\nMetal: ' + str(materials[3]) 
    #stats label
    stats = tk.Label(window, text = stats, font = ('charter', 20), bg = '#00FF00', fg = '#000000')
    stats.place(x = 800, y = 0, anchor = tk.NE)
    #widgets
    widgets = [wall, upgrade_wall_button, repair, upgrade_support_button, back_to_home, wall_details, stats]
    #if player has wall supports add those to widgets
    if levels[0] != 0:
        widgets.append(support_1)
        widgets.append(support_2)
    #binds
    binds = ['<x>', '<w>', '<u>', '<r>', '<s>']
    window.bind('<x>', lambda event: [vanish(event, widgets), unstick(event, binds), home_page(event)]) #bind x key to back to home button
    window.bind('<w>', lambda event: [upgrade(event, 1)]) #bind w key upgrade wall button
    window.bind('<u>', lambda event: [upgrade(event, 1)]) #bind u key upgrade wall button
    window.bind('<r>', lambda event: [how_much_repair_wall(event)]) #bind r key to repair wall button
    window.bind('<s>', lambda event: [upgrade(event, 0)]) #bind s key to upgrade wall support button

##training camp page
def training_page(event):
    #global variables
    global levels, materials, research
    #training camp background
    load = Image.open(training_types[levels[3]] + 'inside.png')
    load = load.resize((800, 600))
    render = ImageTk.PhotoImage(load)
    training = tk.Label(window, image = render, width = 800, height = 600, bg = '#00FF00')
    training.image = render
    training.place(x = 400, y = 300, anchor = tk.CENTER)
    #upgrade training camp button
    upgrade_training_button = tk.Button(window, text = 'Upgrade Training Camp', height = 4, font = ('charter', 10), fg = '#000000')
    upgrade_training_button.place(x = 725, y = 540, anchor = tk.CENTER)
    #recruit army button
    recruit_button = tk.Button(window, text = 'Recruit', height = 4, width = 10, font = ('charter', 10), fg = '#000000')
    recruit_button.place(x = 625, y = 540, anchor = tk.CENTER)
    #train army button
    train_button = tk.Button(window, text = 'Train', height = 4, width = 10, font = ('charter', 10), fg = '#000000')
    train_button.place(x = 550, y = 540, anchor = tk.CENTER)
    #heal army button
    heal_button = tk.Button(window, text = 'Heal', height = 4, width = 10, font = ('charter', 10), fg = '#000000')
    heal_button.place(x = 475, y = 540, anchor = tk.CENTER)
    #attack button
    attack_button = tk.Button(window, text = 'Attack', height = 4, width = 10, font = ('charter', 10), fg = '#000000')
    attack_button.place(x = 400, y = 540, anchor = tk.CENTER)
    #defend button
    defend_button = tk.Button(window, text = 'Defend', height = 4, width = 10, font = ('charter', 10), fg = '#000000')
    defend_button.place(x = 325, y = 540, anchor = tk.CENTER)
    #back to home button
    back_to_home = tk.Button(window, text = 'Home', font = ('charter', 20), width = 7, height = 2, highlightbackground = '#FF0000', fg = '#000000', command = lambda: [vanish(0, widgets), unstick(0, binds), home_page(0)])
    back_to_home.place(x = 0, y = 0, anchor = tk.NW)
    #widgets
    widgets = [training, upgrade_training_button, recruit_button, train_button, heal_button, attack_button, defend_button, back_to_home]
    #binds
    binds = ['<x>']
    window.bind('<x>', lambda event: [vanish(event, widgets), unstick(event, binds), home_page(event)]) #bind x key to back to home button

##home page
def home_page(event):
    #global variables
    global wall_types, research, materials, moves, land, happy, day, levels, support_types
    window.title('Home') #rename window title
    window.config(bg = '#00FF00') #window color
    if 'time' not in research and moves == 3 or 'time' in research and moves == 5: #if player reaches maximum moves per day
        day += 1 #day advances
        moves = 0 #moves goes back to 0
        #taking away food from player, if player not have enough resources, then city happiness goes down by 5
        if materials[1] >= land * 20:
            materials[1] -= land * 20
        else:
            materials[1] = 0
            happy -= 5
    #wall image button
    load = Image.open(wall_types[levels[1]][0])
    load = load.resize((422, 316)) 
    render = ImageTk.PhotoImage(load)
    wall = tk.Button(window, image = render, width = 402, height = 300, command = lambda: [vanish(0, widgets), unstick(0, binds), wall_page(0)])
    wall.image = render
    wall.place(x = 800, y = 600, anchor = tk.SE)
    #training camp button
    load = Image.open(training_types[levels[3]] + '.png')
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    training = tk.Button(window, image = render, width = 201, height = 140, command = lambda: [vanish(0, widgets), unstick(0, binds), training_page(0)])
    training.image = render
    training.place(x = 625, y = 300, anchor = tk.CENTER)
    #market button
    load = Image.open(market_types[levels[6]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    market = tk.Button(window, image = render, width = 186, height = 145)
    market.image = render
    market.place(x = 350, y = 350, anchor = tk.CENTER)
    #research lab button
    load = Image.open(lab_types[levels[4]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    lab = tk.Button(window, image = render, width = 191, height = 120)
    lab.image = render
    lab.place(x = 450, y = 200, anchor = tk.CENTER)
    #district button
    load = Image.open(district_types[levels[5]])
    load = load.resize((211, 158))
    render = ImageTk.PhotoImage(load)
    district = tk.Button(window, image = render, width = 191, height = 150)
    district.image = render
    district.place(x = 0, y = 600, anchor = tk.SW)
    #two wall support images
    if levels[0] != 0: #if wall support not 0
        load = Image.open(support_types[levels[0]][0])
        load = load.resize((20, 29))
        render = ImageTk.PhotoImage(load)
        support_1 = tk.Label(window, image = render, bg = '#00FF00', width = 10, height = 19)
        support_1.image = render
        support_1.place(x = 627, y = 505, anchor = tk.SW)
        support_2 = tk.Label(window, image = render, bg = '#00FF00', width = 10, height = 19)
        support_2.image = render
        if levels[1] == 2 or levels[1] == 3:
            support_2.place(x = 760, y = 485, anchor = tk.SW)
        else:
            support_2.place(x = 757, y = 490, anchor = tk.SW)
    #player stats text
    stats = '$: ' + str(materials[0]) + '  Food: ' + str(materials[1]) + '  Stone: ' + str(materials[2]) + '  Metal: ' + str(materials[3]) + '  Wood: ' + str(materials[4]) + '\nLand: ' + str(land) + '  City Happiness: ' + str(happy) + ' / 100  Day: ' + str(day) + '  Moves played: ' + str(moves) + ' / '
    #moves depending on if time efficiency has been researched
    if 'time' in research:
        stats += '5'
    else:
        stats += '3'
    #player resources label
    stats = tk.Label(window, text = stats, font = ('charter', 20), bg = '#00FF00', fg = '#000000')
    stats.place(x = 400, y = 0, anchor = tk.N)
    widgets = [wall, stats, training, district, lab, market]
    #if player has wall supports add those to widgets
    if levels[0] != 0:
        widgets.append(support_1)
        widgets.append(support_2)
    binds = ['<w>', '<t>']
    window.bind('<w>', lambda event: [vanish(event, widgets), unstick(event, binds), wall_page(event)]) #bind w key to wall image button
    window.bind('<t>', lambda event: [vanish(event, widgets), unstick(event, binds), training_page(event)]) #bind w key to training camp image button

##create start page
def start_page():
    window.title('Empire Simulator') #name window title 
    window.config(bg = '#00FFFF') #window color
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
    start_page() #create start page
    window.mainloop() #mainloop
'''
