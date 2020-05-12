#imports
import random
import time

#vars/lists
silk = 575 #silk
mat = 550 #materials
food = 600 #food
land = 1 #territory
astr = 1 #army strength
ahlth = 100 #army health
wstr = 0 #wall strength
whlth = 100 #wall health
day = 0 #day
hour = '2300' #hour
city = 100 #city happiness
inpt = '' #input
deal = [] #random trade deal 
heal = 0 #amount to heal used for army and wall 
woa = '' #upgrade wall or army (also used for other)
savenum = 0 #save number 
ostr = 0 #enemy strength 
ohlth = 100 #enemy health

#user def functions
#trade tutorial
def trade_help():
    with open('trade.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')

#attack tutorial
def attack_help():
    with open('attack.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')
    
#build tutorial
def build_help():
    with open('build.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')
    
#defend tutorial
def defend_help():
    with open('defend.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')
    
#city happiness tutorial
def city_help():
    with open('city.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')

#retreat tutorial
def retreat_help():
    with open('retreat.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')
    
#save and load tutorial
def save_load_help():
    with open('save_load.txt', 'r') as t:
        for line in t:
            print(line, end = '')
    inpt = input('\n\nEnter to continue\n')
    
#changing the input to the first letter
def get_input(inpt):
    if inpt == '':
        return None
    return inpt[0]

#clear console
def clear():
    print('\n' * 100)
    
#saving
def save():
    global silk #global all vars
    global mat
    global food
    global land
    global astr
    global ahlth
    global wstr
    global whlth
    global day
    global hour
    global city
    global ohlth
    savenum = 1
    with open('saves.txt', 'r') as s: #reading saves.txt to give next save number
        for line in s:
            savenum += 1
    save = open('saves.txt', 'a') #open saves.txt
    save.write('{} {} {} {} {} {} {} {} {} {} {} {}\n'.format(silk, mat, food, land, astr, ahlth, wstr, whlth, day, int(hour), city, ohlth))
    save.close()
    return savenum

#start of game
inpt = input('Welcome to Empire Simulator!\n\nIs this your first time playing?\n') #first time playing will give help
inpt = get_input(inpt)
clear()
if inpt == 'y' or inpt == 'Y': #if it is first time playing run all tutorials
    trade_help() 
    clear()
    attack_help()
    clear()
    build_help()
    clear()
    defend_help()
    clear()
    city_help()
    clear()
    retreat_help()
    clear()
    save_load_help()
clear() 
while 1: #while game is going
    clear() 
    if land == 15:
        raise SystemExit('Congratulations!\nYou have gotten to 15 territory\n\nYou win!\n\nThanks for playing!')
    hour = str(int(hour) + 100) #changing hour
    if int(hour) < 1000:
        hour = '0' + hour
    if hour == '2400': #new day
        hour = '0000'
        day += 1
        if silk < 75: #city consume silk
            city -= 10 #not enough silk city happiness -10
            silk = 0
        else:
            silk -= 75 #city consume silk
            if city != 100: #if not full happiness +2
                city += 2
        if mat < 50: #city consume materials
            city -= 10 #not enough materials city happiness -10
            mat = 0
        else:
            mat -= 50 #city consume materials
            if city != 100: #if not full happiness +2
                city += 2
        if food < 100: #city consume food
            city -= 10 #not enough materials city happiness -10
            food = 0
        else:
            food -= 100 #city consume food
            if city != 100: #if not full happiness +2
                city += 2
        if city < 0: #if city happiness is 0 or less end game
            raise SystemExit('City has revolted. You lose\n')
        if ohlth != 100:
            ohlth += 5 #hurt enemy heals 5 health at new day
    inpt = input('Day {} Hour {}\nCity happiness: {}\n\nYou have:\n{} silk\n{} materials\n{} food\n\nYou have {} territory\n\nCurrent army strength: {}\nCurrent army health: {}\nCurrent wall strength: {}\nCurrent wall health: {}\n\nT: Trade\nA: Attack\nB: Build and upgrade\nH: Help\nS: Save progress\nL: Load progress\nX: Exit (you will lose your progress)\n'.format(day, hour, city, silk, mat, food, land, astr, ahlth, wstr, whlth)) #action
    inpt = get_input(inpt) 
    clear() 
    if inpt == 't' or inpt == 'T': #trade
        inpt = input('You have:\n{} silk\n{} materials\n{} food\n\nWhat do you want to trade for?\n'.format(silk, mat, food)) #choose resource to trade
        inpt = get_input(inpt) 
        clear() 
        if inpt == 's' or inpt == 'S': #silk
            deal = ['silk'] #get resource
        elif inpt == 'm' or inpt == 'M': #materials
            deal = ['materials'] #get resource
        elif inpt == 'f' or inpt == 'F': #food
            deal = ['food'] #get resource
        else: #not valid input
            deal = None
        if deal != None:
            inpt = deal[0]
            while inpt == deal[0]: #random resource that's not the get resource
                inpt = random.randint(1, 3)
                if inpt == 1: #getting resource
                    inpt = silk
                    if inpt != 0:
                        inpt = 'silk'
                elif inpt == 2:
                    inpt = mat
                    if inpt != 0:
                        inpt = 'materials'
                else:
                    inpt = food
                    if inpt != 0:
                        inpt = 'food'
            deal.append(inpt)
            if inpt == 'silk': #getting resource
                inpt = silk
            elif inpt == 'materials':
                inpt = mat
            else:
                inpt = food
            for i in range(2): #paying and getting resource amount
                deal.append(random.randint(1, inpt))
            inpt = input('Trade {} {} to get {} {}?\n'.format(deal[2], deal[1], deal[3], deal[0])) #trade?
            inpt = get_input(inpt) 
            clear() 
            if inpt == 'y' or inpt == 'Y': #trade
                if deal[1] == 'silk':
                    silk -= deal[2]
                elif deal[1] == 'materials':
                    mat -= deal[2]
                else:
                    food -= deal[2]
                if deal[0] == 'silk':
                    silk += deal[3]
                elif deal[0] == 'materials':
                    mat += deal[3]
                else:
                    food += deal[3]
    elif inpt == 'a' or inpt == 'A': #attack
        ostr = land * 5 #setting enemy strength
        woa = 0 #using woa to stop multiple retreat asks
        inpt = input('Your army strength: {}\nYour army health: {}\n\nDo you want to attack an enemy with {} strength and {} health?\n'.format(astr, ahlth, ostr, ohlth)) #ask if attack
        inpt = get_input(inpt)
        clear()
        if inpt == 'y' or inpt == 'Y': #yes to attack
            print('You: {} health    Enemy: {} health'.format(ahlth, ohlth)) #printing army and enemy health
            while ohlth != 0 and ahlth != 0:
                time.sleep(0.01) #short delay 
                inpt = random.randint(1, astr + ostr) #random chance of who takes damage
                if inpt > astr: #formula is army strength / (army strength + enemy strength)
                    ahlth -= 1
                else:
                    ohlth -= 1
                print('You: {} health    Enemy: {} health'.format(ahlth, ohlth)) #printing army and enemy health
                if ahlth == 75 or ahlth == 50 or ahlth == 25 or ahlth == 10 or ahlth == 5:
                    if woa != ahlth:
                        inpt = input('\nYou are at {} health\n\nWould you like to retreat?\n'.format(ahlth)) #ask if retreat
                        inpt = get_input(inpt)
                        clear()
                        if inpt == 'y' or inpt == 'Y': #yes for retreat
                            inpt = input('Army retreated\n\nEnter to continue:\n')
                            break
                        woa = ahlth
            if ahlth == 0: #attack failed
                inpt = input('Attack failed\n\nGo to build and upgrade to heal your army\n\nEnter to continue:\n')
            elif ohlth == 0: #attack success
                land += 1 #add 1 territory
                ohlth = 100 #next enemy health set to 100
                inpt = input('Attack succeeded!\n\nYou have gotten +1 territory\nNow you have {} territory\n\nEnter to continue:\n'.format(land))
    elif inpt == 'b' or inpt == 'B': #build and upgrade
        inpt = input('Current army strength: {}\nCurrent army health: {}\nCurrent wall strength: {}\nCurrent wall health: {}\n\nH: Heal army\nR: Repair wall\nT or A: Train army\nB or W: Build/upgrade wall\n'.format(astr, ahlth, wstr, whlth)) #choose action for build or heal
        inpt = get_input(inpt)
        clear()
        if inpt == 'h' or inpt == 'H' or inpt == 'r' or inpt == 'R': #heal army or wall
            if inpt == 'h' or inpt == 'H':
                if ahlth == 100:
                    inpt = input('Your army is at full health\n\nEnter to continue:\n')
                    inpt = None
                else:
                    woa = True
                    inpt = input('Current army health: {}\n\nHow much do you want to heal the army by?\nType "full" if you want to heal completely\n'.format(ahlth)) #heal by how much
            else:
                if whlth == 100:
                    inpt = input('Your wall is at full health\n\nEnter to continue:\n')
                    inpt = None
                else:
                    woa = False
                    inpt = input('Current wall health: {}\n\nHow much do you want to repair the wall by?\nType "full" if you want to heal completely\n'.format(whlth)) #heal by how much
            if inpt != None:
                clear() 
                heal = get_input(inpt) 
                if heal == 'f' or heal == 'F': #check if input is "full"
                    if woa: 
                        inpt = 100 - ahlth #army
                    else:
                        inpt = 100 - whlth #wall
                try: #check if input is int to avoid error
                    inpt = int(inpt)
                except:
                    inpt = None
                if inpt != None:
                    if woa:
                        heal = 100 - ahlth
                    else:
                        heal = 100 - whlth
                    if inpt < heal: #not full heal
                        heal = inpt
                    if woa: #army
                        if silk >= heal * 5 and mat >= heal * 7 and food >= heal * 10: #check if enough resources
                            inpt = input('Spend {} silk, {} materials, and {} food to heal the army by {}?\n'.format(heal * 5, heal * 7, heal * 10, heal)) #ask if they want to heal
                            inpt = get_input(inpt) 
                            clear() 
                            if inpt == 'y' or inpt == 'Y': #if yes then heal army
                                silk -= heal * 5
                                mat -= heal * 7
                                food -= heal * 10
                                ahlth += heal
                                print('Army healed by {}\n\nEnter to continue\n'.format(heal))
                        else: #not enough resources
                            inpt = input('Not enough resources\nYou need {} silk, {} materials, and {} food\nYou have {} silk, {} materials, and {} food\n\nEnter to continue:\n'.format(heal * 5, heal * 7, heal * 10, silk, mat, food))
                    else: #wall
                        if silk >= heal * 5 and mat >= heal * 10 and food >= heal * 15: #check if enough resources
                            inpt = input('Spend {} silk, {} materials, and {} food to repair the wall by {}?\n'.format(heal * 5, heal *10, heal * 15, heal)) #ask if they want to heal
                            inpt = get_input(inpt) 
                            clear() 
                            if inpt == 'y' or inpt == 'Y': #if yes then repair wall
                                silk -= heal * 5
                                mat -= heal * 7
                                food -= heal * 10
                                whlth += heal
                                print('Wall repaired by {}\n\nEnter to continue\n'.format(heal))
                        else: #not enough resources
                            inpt = input('Not enough resources\nYou need {} silk, {} materials, and {} food\nYou have {} silk, {} materials, and {} food\n\nEnter to continue:\n'.format(heal * 5, heal * 10, heal * 15, silk, mat, food))
        elif inpt == 't' or inpt == 'T' or inpt == 'a' or inpt == 'A' or inpt == 'b' or inpt == 'B' or inpt == 'w' or inpt == 'W':
            if inpt == 't' or inpt == 'T' or inpt == 'a' or inpt == 'A':
                woa = True #train army
                inpt = input('Current army strength: {}\n\nHow much do you want to train your army?\n'.format(astr))
            else:
                woa = False #upgrade wall
                inpt = input('Current wall strength: {}\n\nHow much do you want to upgrade your wall?\n'.format(wstr))
            clear()
            try:
                heal = int(inpt) #using heal for upgrade amount
            except:
                inpt = None #input is not int
            if inpt != None:
                if woa:
                    if silk >= 300 * heal and mat >= 500 * heal and food >= 500 * heal: #training army and has neccessary resources
                        inpt = input('Do you want to train your army by {} for {} silk, {} materials, and {} food?\n'.format(heal, 300 * heal, 500 * heal, 500 * heal)) #checking if he wants to upgrade
                        inpt = get_input(inpt)
                        clear()
                        if inpt == 'y' or inpt == 'Y': #yes for upgrade
                            silk -= 300 * heal
                            mat -= 500 * heal
                            food -= 500 * heal
                            astr += heal
                            inpt = input('Army trained by {}\n\nEnter to continue:\n'.format(heal))
                    else:
                        inpt = input('Not enough resources\nYou need {} silk, {} materials, and {} food\nYou have {} silk, {} materials, and {} food\n\nEnter to continue:\n'.format(heal * 300, heal * 500, heal * 500, silk, mat, food))
                else: 
                    if silk >= 500 * heal and mat >= 800 * heal and food >= 800 * heal: #upgrading wall and has neccessary resources
                        inpt = input('Do you want to upgrade your wall by {} for {} silk, {} materials, and {} food?\n'.format(heal, 500 * heal, 800 * heal, 800 * heal)) #checking if he wants to upgrade
                        inpt = get_input(inpt)
                        clear()
                        if inpt == 'y' or inpt == 'Y': #yes for upgrade
                            silk -= 500 * heal
                            mat -= 800 * heal
                            food -= 800 * heal
                            wstr += heal
                            inpt = input('Wall upgraded by {}\n\nEnter to continue:\n'.format(heal))
                    else:
                        inpt = input('Not enough resources\nYou need {} silk, {} materials, and {} food\nYou have {} silk, {} materials, and {} food\n\nEnter to continue:\n'.format(heal * 500, heal * 800, heal * 800, silk, mat, food))
    elif inpt == 'h' or inpt == 'H': #help
        inpt = input('1. Trade\n2. Attack\n3. Build and Upgrade\n4. Defend\n5. City Happiness\n6. Retreat\n7. Save and Load\n8. All tutorials\n\nChoose tutorial:\n')
        inpt = get_input(inpt)
        clear()
        if inpt == '1' or inpt == 't' or inpt == 'T':
            trade_help()
        elif inpt == '2' or inpt == 'a' or inpt == 'A':
            attack_help()
        elif inpt == '3' or inpt == 'b' or inpt == 'B' or inpt == 'u' or inpt == 'U':
            build_help()
        elif inpt == '4' or inpt == 'd' or inpt == 'D':
            defend_help()
        elif inpt == '5' or inpt == 'c' or inpt == 'C':
            city_help()
        elif inpt == '6' or inpt == 'r' or inpt == 'R':
            retreat_help()
        elif inpt == '7' or inpt == 's' or inpt == 'S' or inpt == 'l' or inpt == 'L':
            save_load_help()
        elif inpt == '8' or inpt == 'a' or inpt == 'A':
            trade_help()
            clear()
            attack_help()
            clear()
            build_help()
            clear()
            defend_help()
            clear()
            city_help()
            clear()
            retreat_help()
            clear()
            save_load_help()
    elif inpt == 's' or inpt == 'S':
        savenum = save() #saving progess
        inpt = input('Your save number is {}\n\nEnter to continue:\n'.format(savenum))
        clear()
    elif inpt == 'l' or inpt == 'L': #load progress
        inpt = input('Save number:\n')
        clear()
        try:
            inpt = int(inpt)
        except:
            inpt = False
        woa = 0 #using woa as a count for lines
        if inpt:
            with open('saves.txt', 'r') as s: #reading saves.txt as s
                for line in s:
                    woa += 1 #check for line
                    if woa == inpt:
                        inpt = line.split()
                        inpt = [int(x) for x in inpt] #changing all the vars
                        silk = inpt[0]
                        mat = inpt[1]
                        food = inpt[2]
                        land = inpt[3]
                        astr = inpt[4]
                        ahlth = inpt[5]
                        wstr = inpt[6]
                        whlth = inpt[7]
                        day = inpt[8]
                        hour = inpt[9]
                        city = inpt[10]
                        ohlth = inpt[11]
                        inpt = input('Progress recovered!\n\nEnter to continue:\n')
                        inpt = True
        if inpt != True:
            inpt = input('Save not found\n\nEnter to continue:\n')
    elif inpt == 'x' or inpt == 'X': #exit game
        inpt = input('Are you sure you want to quit?\n') #fail safe just in case accident
        inpt = get_input(inpt)
        clear() 
        if inpt == 'y' or inpt == 'Y':
            inpt = input('Would you like to save your progress?\n')
            inpt = get_input(inpt)
            clear()
            if inpt == 'y' or inpt == 'Y':
                savenum = save() #saving program
                inpt = input('Your save number is {}\n\nEnter to continue:\n'.format(savenum))
                clear()
            raise SystemExit('Thanks for playing!') #if yes exit program







