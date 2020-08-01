# imports
import datetime, random, socket, time, urllib.request, os, tkinter as tk
from tkinter import messagebox

# files:
window = tk.Tk()
window.title("99 The Card Game")
ISITHOSTORNOST = " "
version = 'BETA 1.4.2'  # TODO change this every time
print("=========================")
print("99 version: " + version)
window.configure(bg="cyan")
a = tk.Label(window, text="99 The Card Game", font=('charter', 30), bg='cyan', fg='black')
a.place(x=400, y=150, anchor=tk.CENTER)
external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8')  # Global ip
name = ""
name1 = ""  # oppoent name
communications = ''  # host send
port = 12345  # def
theirEIP = ""
host = ""
MPorSP = 0  # 1 is mp 0 is sp
namething = ""  # name of file to log game into
# vars (game)#
added = 0
cardl = []  # cards left
sumc = 0  # sum of cards
cardn = 0  # amount of cards per player
pcard = []  # player cards
inpt = ''  # input
nums = ['2', '3', '4', '5', '6', '7', '8', '9', '10']  # number cards
# single player
botNames = ["SoccerMom", "PlasticFoods", "BustedKneeCap", "gitPushOrca", "godlyPro", "iFrag", "BotMoooo"]
bcard = []  # bot cards
# multi player#
turn = 0
xpgained = 0
rank = " "
xp = 0
completed = ""
ranks = ["Bronze", "Silver", "Gold", "Dedicated", "Honor", "Veteran", "Professional", "Platinum", "Moolius", "Mooclear"]
rankscore = [250, 500, 800, 1000, 1350, 1500, 2000, 2500, 3000]


def exit():
    raise SystemExit("Game Stopped")


Sss = tk.Button(window, text="EXIT",
                command=lambda: [exit()])
Sss.place(x=750, y=0)


def clearPg():
    print("\n" * 100)


def submitUsername(un):  # un = username
    global name
    name = str(un)
    XPFINDR = open("saveData.txt", "w")
    XPFINDR.write(str(rank) + "\n" + name + "true")
    XPFINDR.close()
    # TODO save to file here


def username():
    a = tk.Label(window, text=("Username:"), font=('charter', 30), bg='cyan', fg='black')  # username text
    a.place(x=400, y=150, anchor=tk.CENTER)
    entry1 = tk.Entry(window)  # make window for input
    entry1.place(x=400, y=300, anchor=tk.CENTER)  # anchor input box
    savetousername = tk.Button(text='Submit', command=lambda: [submitUsername(entry1.get())])  # submit button
    savetousername.place(x=475, y=285)  # submit button place


def rankchecklevel(print, ranka, calculate):
    global ranks
    global rankscore
    global rank
    r = 0
    if 0 <= ranka < 250:
        R = 0
        ranka = ranks[0]
    elif 250 <= ranka < 500:
        R = 1
        ranka = ranks[1]
    elif 500 <= ranka < 800:
        R = 2
        ranka = ranks[2]
    elif 800 <= ranka < 1000:
        R = 3
        ranka = ranks[3]
    elif 1000 <= ranka < 1350:
        R = 4
        ranka = ranks[4]
    elif 1350 <= ranka < 1500:
        R = 5
        rank = ranks[5]
    elif 1500 <= ranka < 2000:
        R = 6
        ranka = ranks[6]
    elif 2000 <= ranka < 2500:
        R = 7
        ranka = ranks[7]
    elif 2500 <= ranka < 3000:
        R = 8
        ranka = ranks[8]
    elif 3000 <= ranka:
        R = 9
        ranka = ranks[9]
    # TODO work on this for calcs
    if print and calculate == 0:
        return ranka
    if calculate == 1:
        calculations = rankscore[r] - rank
        return calculations
    if calculate == 2:
        ranka = ranks[R + 1]
        return ranka


# ranked
def destroySave():
    a = tk.messagebox.askyesno("CONFIRM DELETION",
                               "ARE YOU SURE YOU WANT TO DELETE THIS SAVE?(IT'LL BE GONE FOR A LONG LONG TIME)!")
    if a:
        try:
            os.remove("saveData.txt")
        except:
            msg = messagebox.showinfo("Critical Error", "Could Not Delete File.")
            raise SystemExit("CRITICAL ERROR")
        msg = messagebox.showinfo("Success", "save deleted!")


def buttonifyFail():
    a = tk.messagebox.askyesno("ERROR",
                               "SAVE CORRUPTED. DELETE?")
    if a:
        destroySave()


def buttonifySuccess():
    a = tk.Label(window, text=("Save Found! \nINFO:\nRank:" + str(rankchecklevel(1, rank, 0)) + "(" + str(
        rank) + ")\nUsername:" + str(name)), font=('charter', 30), bg='cyan', fg='black')
    a.place(x=400, y=150, anchor=tk.CENTER)
    ass = tk.Button(window, text="Load",
                    command=lambda: [destroyBTN(ass, bss, css, 0)])
    ass.place(x=200, y=300)
    bss = tk.Button(window, text="Cancel",
                    command=lambda: [destroyBTN(ass, bss, css, 0)])
    bss.place(x=350, y=300)
    css = tk.Button(window, text="Delete",
                    command=lambda: [destroyBTN(ass, bss, css, 0), destroySave()])
    css.place(x=500, y=300)


def rankedcheck(loadnew):
    global rank
    global name
    global completed
    if loadnew == 0:
        if os.path.exists("saveData.txt"):
            with open('saveData.txt', 'r') as XPFINDR:
                try:
                    data = XPFINDR.readlines()
                    rank = int(data[0])
                    name = data[1]
                    completed = data[2]
                    print(1)
                    if completed == "false":
                        Sbb = tk.Button(window, text="[RANKED PENALTY] \n YOU LEFT A GAME: -10 XP\n Click To Continue",
                                        command=lambda: [destroyBTN(0, 0, Sbb, 0)])
                        Sbb.place(x=160, y=200)
                        rank -= 10
                    buttonifySuccess()
                except:
                    XPFINDR.close()
                    buttonifyFail()
            XPFINDR.close()
        else:
            a = tk.messagebox.showinfo("ERROR",
                                       "NO SAVES FOUND. MAKE NEW SAVE?")
            rankedcheck(1)
    elif loadnew == 1:
        a = tk.messagebox.askyesno("CONFIRM",
                                   "Make a new save? It will overwrite your existing file.")
        if a:
            XPFINDR = open("saveData.txt", "w+")
            rank = 0
            XPFINDR.write(str(rank))
            XPFINDR.close()
            a = tk.messagebox.showinfo("Success!",
                                       "You have made a new save!")
            username()


# game stuff
def cardSetup():
    global cardl
    global cardn
    global pcard
    global bcard
    ##ask for amount of cards per player
    if inpt != 1:
        while True:
            print("=========================")
            print("How many cards per player? (1 to 10)")
            print("=========================")
            cardn = input('>>>')
            try:  # trying to set input to integer
                cardn = int(cardn)
                if cardn <= 10:
                    break
                print('!!!ERROR: Input was greater than 10\n')
            except:
                print('!!!ERROR: Input was not an integer\n')
    ##giving cards
    for i in range(cardn):  # player
        pcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
    for i in range(cardn):  # bot
        bcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))


# ip reacher (loc)
def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP


def setupH():  # setup the host
    global ISITHOSTORNOST
    global name
    global port
    global external_ip
    global name1
    global communications
    global theirEIP
    global turn
    global namething
    ISITHOSTORNOST = "host"
    turn = random.randint(0, 1)
    print("=========================")
    print("port (1-5 digit)")
    print("=========================")
    port = int(input(">>>"))  # port
    communications = socket.socket()
    communications.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    host = get_ip()  # socket stuff
    communications.bind((host, port))
    clearPg()
    print("=========IP(Local)===========")
    print(host)  # print out local ip
    print("=========IP(Global)==========")
    print(external_ip)  # print global ip
    print("============PORT=============")
    print(port)  # print port for global ip
    print("=============================")
    print("Room started\nWaiting for connections...")
    communications.listen(1)  # wait for ppl to join
    communications, adr = communications.accept()  # if see ppl accept it
    name = name.encode()  # send your name to them
    communications.sendall(name)  # ^^
    name = name.decode()
    name1 = communications.recv(1024)  # receive their name
    name1 = name1.decode()
    external_ip = external_ip.encode()  # send external ip
    communications.sendall(external_ip)
    host = host.encode()  # send local ip
    communications.sendall(host)
    host = host.decode()
    external_ip = external_ip.decode()
    theirIP = communications.recv(1024)  # receive their ip (local)
    theirIP = theirIP.decode()
    print(theirIP)
    theirEIP = communications.recv(1024)  # receive their ip (global)
    theirEIP = theirEIP.decode()
    turn = str(turn).encode()  # send your order of cards to them
    communications.sendall(turn)
    turn.decode()
    turn = int(turn)
    if turn == 1:
        turn = 0
    elif turn == 0:
        turn = 1
    print(theirEIP)
    temptuple = (
        "Game", str(datetime.datetime.now()),
        ".txt")  # make a string that can be converted into file (no spaces or _)
    namething = str("".join(temptuple))
    namething = namething.replace(' ', '_')
    namething = namething.replace(':', '_')
    h = open(namething, "w+")  # make a file with the name
    temptuple1 = (
        "From HOST, on port: ", str(port), ": game between ", name, " [you] (", host, ")(", external_ip, ") and ",
        name1,
        " (", theirIP, ") (", theirEIP, ")\n ================= \n")
    # temptuple1 = ("conversation between ",name," (",host,") and ",name1," (",theirIP,") \n ================= \n")
    temptuple1 = "".join(temptuple1)
    h.write(str(temptuple1))
    h.close()
    clearPg()
    print("=========================")
    print("successfully connected to game. Your Oppoent:" + name1)
    print("=========================")  # adsf


def setupN():
    global ISITHOSTORNOST
    global name
    global port
    global external_ip
    global name1
    global communications
    global theirEIP
    global turn
    global namething
    ISITHOSTORNOST = "nost"
    print("=========================")
    print("port (1-5 digit)")
    print("=========================")
    port = int(input(">>>"))
    clearPg()
    ipplaceholder = get_ip()
    communications = socket.socket()
    communications.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # tries to reuse socket
    print("=======IP(Local)=========")
    print(ipplaceholder)  # local ip
    print("=======IP(Global)========")
    print(external_ip)  # glob ip
    print("=========Port============")
    print(port)  # port
    print("==Connect To (Enter IP)==")
    theirEIP = input(str(">>>"))  # enter ip to connect to
    communications.connect((theirEIP, port))
    name1 = communications.recv(1024)  # recieve their name
    name1 = name1.decode()
    name = name.encode()  # encode and send ur name
    communications.send(name)
    name = name.decode()  # eecode name after sending
    theirEIP = communications.recv(1024)  # receive their ip (ext)
    theirEIP = theirEIP.decode()
    theirIP = communications.recv(1024)  # recv their ip (loc)
    theirIP = theirIP.decode()
    print(ipplaceholder)
    ipplaceholder = ipplaceholder.encode()  # send local ip
    communications.send(ipplaceholder)
    ipplaceholder = ipplaceholder.decode()
    time.sleep(0.5)
    extern = external_ip.encode()
    communications.send(extern)  # send glob ip
    turn = communications.recv(1024)  # Recv game order
    turn = turn.decode()
    turn = int(turn)
    temptuple = ("Game", str(datetime.datetime.now()), ".txt")
    namething = str("".join(temptuple))
    namething = namething.replace(' ', '_')
    namething = namething.replace(':', '_')
    h = open(namething, "w+")
    temptuple1 = (
        "From NOST, on port: ", str(port), ": game between ", name, " [you] (", ipplaceholder, ")(", external_ip,
        ") and ", name1, " (", theirIP, ") (", theirEIP, ")\n ================= \n")
    temptuple1 = "".join(temptuple1)
    h.write(str(temptuple1))
    h.close()
    clearPg()
    print("=========================")
    print("successfully connected to game. Your Oppoent:" + name1)
    print("=========================")


def multiplayer():
    global cardl
    global cardn
    global pcard
    global bcard
    global communications
    global namething
    h = open(namething, "a")
    if turn == 1:
        cardSetup()
        communications.send(str(cardn).encode())  # send number of cards
        m = communications.recv(1024)  # recv feedback(else it jams)
        cardm = len(cardl)  # new var count length of cards
        communications.send(str(cardm).encode())  # send over
        m = communications.recv(1024)  # recv feedback
        h.write("your cards: ")
        for i in range(cardn):
            pcard[i] = str(pcard[i])  # send all items of the array for host card
            pcard[i] = pcard[i].encode()
            communications.send(pcard[i])
            pcard[i] = pcard[i].decode()  # decode it after
            pcard[i] = int(pcard[i])
            m = communications.recv(1024)  # recv fedback (jam)
            h.write(str(pcard[i]))
        h.write("\ntheir cards: ")
        for i in range(cardn):
            bcard[i] = str(bcard[i])  # send all items of the array for nost card
            bcard[i] = bcard[i].encode()
            communications.send(bcard[i])
            bcard[i] = bcard[i].decode()
            bcard[i] = int(bcard[i])
            m = communications.recv(1024)  # recv fedback (jam)
            h.write(str(bcard[i]))
        for i in range(cardm):
            cardl[i] = str(cardl[i])  # send all items of the rest of the deck unused
            cardl[i] = cardl[i].encode()
            communications.send(cardl[i])
            cardl[i] = cardl[i].decode()
            cardl[i] = int(cardl[i])
            m = communications.recv(1024)
        clearPg()
        print("=========================")
        print("Game Setup Success!")
        print("=========================")
        print("\n\n\n")
    else:
        print("=========================")
        print("waiting for oppoent...")
        print("=========================")
        cardn = communications.recv(1024)
        cardn = cardn.decode()
        cardn = int(cardn)
        md = "ok"
        communications.send(md.encode())
        cardm = communications.recv(1024)
        cardm = cardm.decode()
        cardm = int(cardm)
        communications.send(md.encode())
        pcard = [0 for x in range(cardn)]  # fucc u out of bound error raaa
        bcard = [0 for x in range(cardn)]
        cardl = [0 for x in range(cardm)]  # makes a big array of the rest of the cards depending on how many left
        h.write("\ntheir cards: ")
        for i in range(cardn):
            bcard[i] = communications.recv(
                1024)  # flipped, that wya you recieve host cards as oppoent cards and not your cards lol
            bcard[i] = bcard[i].decode()
            bcard[i] = int(bcard[i])
            md = "ok"
            communications.send(md.encode())  # send unjam thing
            h.write(str(bcard[i]))
        h.write("your cards: ")
        for i in range(cardn):
            pcard[i] = communications.recv(1024)
            pcard[i] = pcard[i].decode()  # recv card lists
            pcard[i] = int(pcard[i])
            communications.send(md.encode())  # repeat for nost card.
            h.write(str(pcard[i]))
        for i in range(cardm):
            cardl[i] = communications.recv(1024)  # recv rest of deck
            cardl[i] = cardl[i].decode()
            cardl[i] = int(cardl[i])
            communications.send(md.encode())
        clearPg()
        print("=========================")
        print("Game Setup Success!")
        print("=========================")
        print("\n\n\n")
    h.write("\nFinished setting up game!")
    h.close()


# user def functions
##player replace card
def p_replace_card(c):
    global MPorSP
    global added
    global cardl
    global cardn
    global pcard
    global bcard
    global name
    global communications
    global namething
    count = -1
    for i in pcard:
        count += 1
        if i == c:
            pcard.pop(count)
            r = random.randint(0, len(cardl) - 1)
            pcard.append(cardl.pop(r))
            if MPorSP == 1:
                cardm = len(cardl)  # new var count length of cards
                communications.send(str(cardm).encode())
                h = open(namething, "a")
                m = communications.recv(1024)
                for i in range(cardn):
                    pcard[i] = str(pcard[i])  # send all items of the array for host card
                    pcard[i] = pcard[i].encode()
                    communications.send(pcard[i])
                    pcard[i] = pcard[i].decode()  # decode it after
                    pcard[i] = int(pcard[i])
                    m = communications.recv(1024)  # recv fedback (jam)
                    h.write(str(pcard[i]))
                for i in range(cardm):
                    cardl[i] = str(cardl[i])  # send all items of the rest of the deck unused
                    cardl[i] = cardl[i].encode()
                    communications.send(cardl[i])
                    cardl[i] = cardl[i].decode()
                    cardl[i] = int(cardl[i])
                    m = communications.recv(1024)
                communications.send((str(added)).encode())
                communications.send((str(sumc)).encode())
                temptuple1 = (
                    "\n", name, " Played: ", str(c), " Total Deck Value: ", str(sumc)
                )
                temptuple1 = "".join(temptuple1)
                h.write(str(temptuple1))
                h.close()
            break


##bot replace card
def b_replace_card(c):
    global bcard
    count = -1
    for i in bcard:
        count += 1
        if i == c:
            bcard.pop(count)
            bcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
            break


def isOverAHunnit(l):
    global ISITHOSTORNOST
    global sumc
    global xpgained
    global communications
    global name
    global xp
    if sumc > 99:
        if ISITHOSTORNOST == "host":
            communications.close()
        if l == 0:
            h = open(namething, "a")
            h.write("\n\nYou win!")
            h.close()
            xp = random.randint(30, 50)
            xpgained += xp
            print(
                '\n\nYou win! + ' + str(
                    xp) + " Ranked XP! Only " + str(rankchecklevel(0, rank, 1)) + " More to " + str(rankchecklevel(0,
                                                                                                                   rank,
                                                                                                                   2)))  # rank
            a = input('You won!, back to the lobby. \nEnter to Continue')
        else:
            h = open(namething, "a")
            h.write("\n\nYou lose!")
            h.close()
            xp = (random.randint(10, 30)) * -1
            xpgained += xp
            print(
                '\n\nYou lose!  ' + str(
                    xp) + " Ranked XP!  " + str(rankchecklevel(0, rank, 1)) + " More to " + str(rankchecklevel(0,
                                                                                                               rank,
                                                                                                               2)))  # rank
            a = input('You Lost!, back to the lobby. \nEnter to Continue')


##player plays
def player():
    global pcard
    global cardl
    global sumc
    global MPorSP
    global added
    global xpgained
    global communications
    global xp
    print("=========================")
    print("Your Cards: ")
    for i in pcard:  # print cards
        i = int(i)
        if i == 1:
            print('[A]', end='')
        elif i == 11:
            print('[Ja]', end='')
        elif i == 12:
            print('[Q]', end='')
        elif i == 13:
            print('[K]', end='')
        elif i == 14:
            print('[Joker]', end='')
        else:
            print('[{}]'.format(i), end='')
            # print(type(pcard[i]))
    print("\n=========================")
    while True:
        inpt = input('Choose a card to play:\n\n>>>')
        if inpt != '':
            if inpt[0] == 'a' or inpt[0] == 'A':  # ace
                if 1 in pcard:
                    while True:
                        inpt = input('>Should Ace be 1 or 11?<\n')
                        if inpt == '1' or inpt == '11':
                            if inpt == '1':
                                sumc += 1
                                added = 1
                            else:
                                sumc += 11
                                added = 11
                            p_replace_card(1)
                            break
                        else:
                            print('\n!!!ERROR: Input was not 1 or 11\n')
                    break
            elif inpt[0] == 'j' or inpt[0] == 'J':
                if len(inpt) > 1:
                    if inpt[1] == 'a' or inpt[1] == 'A':  # jack
                        if 11 in pcard:
                            sumc += 10
                            added = 10
                            p_replace_card(11)
                            break
                    elif inpt[1] == 'o' or inpt[1] == 'O':  # joker
                        if 14 in pcard:
                            sumc = 99
                            added = 1000
                            p_replace_card(14)
                            break
            elif inpt[0] == 'q' or inpt[0] == 'Q':  # queen
                if 12 in pcard:
                    sumc += 10
                    added = 10
                    p_replace_card(12)
                    break
            elif inpt[0] == 'k' or inpt[0] == 'K':  # king
                if 13 in pcard:
                    sumc = 99
                    added = 1000
                    p_replace_card(13)
                    break
            elif inpt in nums:
                inpt = int(inpt)
                if inpt == 4:  # 4
                    p_replace_card(4)
                    added = 0
                    break
                elif inpt == 9:  # 9
                    p_replace_card(9)
                    added = 0
                    break
                elif inpt == 10:  # 10
                    sumc -= 10
                    p_replace_card(10)
                    added = -10
                    break
                else:  # other numbers
                    sumc += inpt
                    added = inpt
                    p_replace_card(inpt)
                    break
    if sumc > 99 and MPorSP == 0:
        clearPg()
        print("=========================")
        print('Bot cards:\n')
        for i in bcard:  # print cards
            if i == 1:
                print('[A]', end='')
            elif i == 11:
                print('[J]', end='')
            elif i == 12:
                print('[Q]', end='')
            elif i == 13:
                print('[K]', end='')
            elif i == 14:
                print('[Joker]', end='')
            else:
                print('[{}]'.format(i), end='')
        xp = (random.randint(10, 30)) * -1
        xpgained += xp
        print(
            '\n\nYou lose!  ' + str(
                xp) + " Ranked XP!  " + str(rankchecklevel(0, rank, 1)) + " More to " + str(rankchecklevel(0,
                                                                                                           rank,
                                                                                                           2)))
        a = input('You lost, back to the lobby. \nEnter to Continue')
    #    else:
    #       isOverAHunnit(1)
    print('Sum: {}'.format(sumc))
    if sumc <= 99:
        clearPg()  # potential bug
    else:
        print("=========================")


##bot plays
def bot():  # push now but bug here
    global bcard
    global cardl
    global sumc
    global xpgained
    global xp
    clearPg()
    print("=========================")
    nums = [2, 3, 5, 6, 7, 8]
    power = True  # does the bot have all power cards?
    if sumc <= 88:
        for i in bcard:
            if i in nums:
                power = False
                break
        if not power:
            while True:
                power = bcard[random.randint(0, cardn - 1)]
                if power in nums:
                    sumc += power
                    print('{} played: {}\nSum: {}'.format(botName, power, sumc))
                    break
        else:
            power = bcard[random.randint(0, cardn - 1)]
            if power == 1:
                inpt = random.randint(1, 2)
                if inpt == 1:
                    sumc += 1
                    print('{} played: A(1)\nSum: {}'.format(botName, sumc))
                else:
                    sumc += 11
                    print('{} played: A(11)\nSum: {}'.format(botName, sumc))
            else:
                if power == 10:
                    sumc -= 10
                    print('{} played: 10\nSum: {}'.format(botName, sumc))
                elif power == 11 or power == 12:
                    sumc += 10
                    if power == 11:
                        print('{} played: J\nSum: {}'.format(botName, sumc))
                    else:
                        print('{} played: Q\nSum: {}'.format(botName, sumc))
                else:
                    sumc = 99
                    if power == 13:
                        print('{} played: K\nSum: {}'.format(botName, sumc))
                    else:
                        print('{} played: Joker\nSum: {}'.format(botName, sumc))
        b_replace_card(power)
    else:
        played = False  # did bot play yet?
        for i in bcard:
            if i in nums and i + sumc <= 99:
                sumc += i
                print('{} played: {}\nSum: {}'.format(botName, i, sumc))
                played = True
        if not played:
            if sumc + 10 <= 99:
                if 11 in bcard or 12 in bcard:
                    sumc += 10
                    if 11 in bcard:
                        i = 11
                        print('{} played: J\nSum: {}'.format(botName, sumc))
                    else:
                        i = 12
                        print('{} played: Q\nSum: {}'.format(botName, sumc))
                    played = True
        if not played:
            if 1 in bcard and sumc < 99:
                sumc += 1
                print('{} played: A(1)\nSum: {}'.format(botName, sumc))
            else:
                if 13 in bcard or 14 in bcard:
                    sumc = 99
                    if 13 in bcard:
                        i = 13
                        print('{} played: K\nSum: {}'.format(botName, sumc))
                    else:
                        i = 14
                        print('{} played: Joker\nSum: {}'.format(botName, sumc))
                elif 4 in bcard:
                    i = 4
                    print('{} played: 4\nSum: {}'.format(botName, sumc))
                elif 9 in bcard:
                    i = 9
                    print('{} played: 9\nSum: {}'.format(botName, sumc))
                elif 10 in bcard:
                    sumc -= 10
                    i = 10
                    print('{} played: 10\nSum: {}'.format(botName, sumc))
                else:
                    clearPg()
                    print("=========================")
                    print('Bot cards:\n')
                    for i in bcard:  # print cards
                        if i == 1:
                            print('[A]', end='')
                        elif i == 11:
                            print('[J]', end='')
                        elif i == 12:
                            print('[Q]', end='')
                        elif i == 13:
                            print('[K]', end='')
                        elif i == 14:
                            print('[Joker]', end='')
                        else:
                            print('[{}]'.format(i), end='')
                    xp = random.randint(30, 50)
                    xpgained += xp
                    print(
                        '\n\nYou win! + ' + str(
                            xp) + " Ranked XP! Only " + str(rankchecklevel(0, rank, 1)) + " More to " + str(
                            rankchecklevel(0,
                                           rank,
                                           2)))  # rank
                    a = input('You won!, back to the lobby. \nEnter to Continue')
                    sumc = 103  # stops bugging th eprogram and keep the game going evne you win
        b_replace_card(i)


##turn test
def play(n):
    if n == 0:
        if sumc < 100:
            bot()
    else:
        if sumc < 100:
            player()


def checkforcardempty():
    global cardl
    if cardl == []:  # if cards all used up recycle deck
        for i in range(1, 14):  # TODO work on making recycled deck not have duplicates and multiplayer
            for k in range(4):
                cardl.append(i)
        for i in range(2):
            cardl.append(14)


def recvplay():
    global communications
    global sumc
    global name1
    global cardl
    global cardn
    global pcard
    global bcard
    global namething
    clearPg()  # new
    print("waiting for oppoent...")
    md = "ok"
    cardm = communications.recv(1024)
    clearPg()
    cardm = cardm.decode()
    cardm = int(cardm)
    communications.send(md.encode())
    for i in range(cardn):
        bcard[i] = communications.recv(
            1024)  # flipped, that wya you recieve host cards as oppoent cards and not your cards lol
        bcard[i] = bcard[i].decode()
        bcard[i] = int(bcard[i])
        communications.send(md.encode())  # send unjam thing
    for i in range(cardm):
        cardl[i] = communications.recv(1024)  # recv rest of deck
        cardl[i] = cardl[i].decode()
        cardl[i] = int(cardl[i])
        communications.send(md.encode())
    added = communications.recv(1024)  # decode value added
    added = added.decode()
    added = int(added)
    sumc = communications.recv(1024)
    sumc = sumc.decode()
    sumc = int(sumc)
    newcardplayedName = ""
    if added == 1 or added == 11:
        newcardplayedName = "Ace"
    elif added == 1000:
        newcardplayedName = "NINETYNINER"
    elif added == 0:
        newcardplayedName = "O"
    elif added == -10:
        newcardplayedName = "-10"
    else:
        newcardplayedName = str(added)  # lol forgot to put this in that's why it didnt work
    print("=========================")
    print(name1 + " Played:" + newcardplayedName + "\n Sum now: " + str(sumc))  # prints what person played and thing
    h = open(namething, "a")
    temptuple1 = (
        "\n", name1, " Played: ", str(newcardplayedName), " Total Deck Value: ", str(sumc)
    )
    temptuple1 = "".join(temptuple1)
    h.write(str(temptuple1))
    h.close()


def change(v):
    global MPorSP
    MPorSP = v


def destroyBTN(M, L, S, G):
    if L != 0:
        L.destroy()
    if M != 0:
        M.destroy()
    if S != 0:
        S.destroy()
    if G != 0:
        G.destroy()


# pre game set ups
window.geometry("800x600")


def selectMode():
    S = tk.Button(window, text="SinglePlayer", command=lambda: [rankedcheck(), destroyBTN(M, 0, S, 0)])
    S.place(x=160, y=80)
    M = tk.Button(window, text="MultiPlayer", command=lambda: [rankedcheck(), destroyBTN(M, 0, S, 0)])
    M.place(x=240, y=80)


def load():
    a = tk.Label(window, text="Saves", font=('charter', 30), bg='cyan', fg='black')
    a.place(x=400, y=150, anchor=tk.CENTER)
    L = tk.Button(window, text="Load Save", command=lambda: [rankedcheck(0), destroyBTN(La, L, a, 0)])
    L.place(x=300, y=300)
    La = tk.Button(window, text="New Save", command=lambda: [rankedcheck(1), destroyBTN(L, La, a, 0)])
    La.place(x=500, y=300)


def inptchange(o):
    global inpt
    if o == 1:
        inpt = "Y"
    elif o == 2:
        inpt = "N"
    elif o == 3:
        inpt = "D"


def tutorial(asdf):
    if asdf == 0:
        N = tk.Button(window,
                      text="Objective of game: Get to 99 but don\'t go over. \nMake the other person go over 99 to "
                           "win\nHow to play: When you play a card it adds to the sum of all the cards.\n For "
                           "example if the first card played was 6 and the second card played \nwas 3, "
                           "the sum would be 9\n\n There are special cards in this game \nCard values:\nA: 1 or 11 (your choice)\n2: 2\n3: 3\n4: 0\n5: "
                           "5\n6: 6\n7: 7\n8: 8\n9: 0\n10: -10\nJ: 10\nQ: 10\nK: Automatically to 99\nJoker: "
                           "Automatically to 99\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n CLICK HERE TO CONTINUE"
                      , bg="cyan", command=lambda: [destroyBTN(N, 0, 0, 0), load()])
        N.place(x=0, y=0)


print("=========================")
# rankedcheck()  # new may break
A = tk.Button(window, text="Tutorial", width=20, height=3, command=lambda: [tutorial(0), destroyBTN(A, a, V, 0)])
A.place(x=200, y=300)
V = tk.Button(window, text="Start", width=20, height=3, command=lambda: [load(), destroyBTN(A, V, a, 0)])
V.place(x=400, y=300)

window.mainloop()
while True:
    # XPFINDR = open("saveData.txt", "w")
    #    bcd = rank + xp
    # XPFINDR.write(str(bcd) + "\n" + name + "true")
    # XPFINDR.close()
    ##filling cardl
    cardl = []  # cards left
    for i in range(1, 14):
        for k in range(4):
            cardl.append(i)
    for i in range(2):
        cardl.append(14)
    # files:
    external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8')  # Global ip
    name1 = ""  # oppoent name
    communications = ''  # host send
    port = 12345  # def
    theirEIP = ""
    host = ""
    MPorSP = 0  # 1 is mp 0 is sp
    namething = ""  # name of file to log game into
    # vars (game)
    added = 0
    sumc = 0  # sum of cards
    cardn = 0  # amount of cards per player
    pcard = []  # player cards
    inpt = ''  # input
    nums = ['2', '3', '4', '5', '6', '7', '8', '9', '10']  # number cards
    # single player
    botNames = ["SoccerMom", "PlasticFoods", "BustedKneeCap", "gitPushOrca", "godlyPro", "iFrag", "BotMoooo"]
    bcard = []  # bot cards
    # multi player
    turn = 0
    botName = botNames[random.randint(0, 4)]
    ##ask if it is first time playing
    '''
    # MP or DOM
    clearPg()
    if inpt != '':
        inpt = inpt[0]  # setting input to first letter if input is not enter
    '''
    if inpt == '2':
        MPorSP = 1
        print("=========================")
        print("[1]Host or [2]Nost?")
        print("=========================")
        inpt = input('>>>')
        clearPg()
        if inpt != '':
            inpt = inpt[0]  # setting input to first letter if input is not enter
        if inpt == '1':
            setupH()  # setupMPshenanananannanannananangans
        elif inpt == '2':
            setupN()  # setupMP NOST HAHAHHAHA NOSTING U KIDDING ME IDOT I TOLD U U GET FREE ISIMPYT SUBIF U GET HOST
            # SDJGHLSKJFJKLDKLJFLH
        multiplayer()
    '''
    elif inpt == 'x':
        if xpgained > 0:
            raise SystemExit("Successfully Exited. You have earned " + str(xpgained) + " XP Today. Well Done")
        else:
            raise SystemExit("Successfully Exited. You have lost " + str(xpgained) + " XP Today. Better Luck Next Time")
    elif inpt == '1':
        cardSetup()
    '''
    # gameplay
    if MPorSP == 0:
        # XPFINDR = open("saveData.txt", "w")
        # XPFINDR.write(str(rank) + "\n" + name + "false")
        # XPFINDR.close()
        clearPg()
        print("=========================")
        print("Do you want to go first?")
        print("=========================")
        inpt = input('>>>')  # add difficulties later
        clearPg()
        if inpt != '':
            inpt = inpt[0]
        if inpt == 'y' or inpt == 'Y':
            inpt = 0
        else:
            inpt = 1
        clearPg()
        print("=========================")
        print("Oppoent is: " + botName)
        while sumc < 100:
            inpt += 1
            play(inpt % 2)
            checkforcardempty()
        clearPg()
    else:
        # XPFINDR = open("saveData.txt", "w")
        # XPFINDR.write(str(rank) + "\n" + name + "false")
        # XPFINDR.close()
        while sumc < 100:
            if turn == 0:
                if sumc < 100:
                    try:
                        player()  # second
                    except:
                        break
                    isOverAHunnit(1)
                if sumc < 100:
                    try:
                        recvplay()
                    except:
                        isOverAHunnit(0)
                        break
                    isOverAHunnit(0)
            elif turn == 1:
                if sumc < 100:
                    try:
                        recvplay()  # first
                    except:
                        isOverAHunnit(0)
                        break
                    isOverAHunnit(0)
                if sumc < 100:
                    try:
                        player()
                    except:
                        break
                    isOverAHunnit(1)
            checkforcardempty()
