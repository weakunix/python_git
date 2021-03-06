# imports
import datetime, random, socket, time, threading, urllib.request, os, tkinter as tk
from tkinter import messagebox
from PIL import Image, ImageTk
from sys import platform

#depricated
# files:
u = 0
window = tk.Tk()  # make window of TK as window var
window.title("99 The Card Game")  # title the window
ISITHOSTORNOST = " "  # is the device hosting or a client
version = 'BETA 1.5.7'  # TODO change this every time 99 version
assss = tk.Label(window, text=version, font=('charter', 10), bg='cyan', fg='black')  # print 99 version
assss.place(x=400, y=200, anchor=tk.CENTER)  # center text
window.configure(bg="cyan")  # background of the window
a = tk.Label(window, text="99 The Card Game", font=('charter', 30), bg='cyan', fg='black')  # print 99 the card game
a.place(x=400, y=150, anchor=tk.CENTER)
if platform == "darwin":
    print("NOTE: You are running MACOS, the external IP identifier will not work")
    external_ip = "111.111.111.111"
else:
    pass
    external_ip = "111.111.111.111"  # TODO FIX THIS
    # external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8')  # Global ip
name = ""  # your name
name1 = ""  # oppoent name
communications = ''  # host send
port = 12345  # def
theirEIP = ""  # their external ip
host = ""  # host's ip
MPorSP = 0  # 1 is mp 0 is sp
namething = ""  # name of file to log game into
# vars (game)#
added = 0  # added number to sumc value
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
turn = 0  # turn for mp
xpgained = 0  # how much xp gaiined off of 1 game
rank = " "  # what rank are you
xp = 0  # xp
botName = botNames[random.randint(0, 4)]
completed = ""  # if you finished the game (prevents leaving during a game)
ranks = ["Bronze", "Silver", "Gold", "Dedicated", "Honor", "Veteran", "Professional", "Platinum", "Moolius",
         "Mooclear"]  # the ranks
confirmcards = False
cardl = []  # cards left
for i in range(1, 14):
    for k in range(4):
        cardl.append(i)
for i in range(2):
    cardl.append(14)

rankscore = [250, 500, 800, 1000, 1350, 1500, 2000, 2500, 3000]  # the score you need to advance to the next rank


def destroyBTN(M, L, S, G):
    if L != 0:
        L.destroy()
    if M != 0:
        M.destroy()
    if S != 0:
        S.destroy()
    if G != 0:
        G.destroy()


def clearPg():  # clear the page in console (deprecated)
    print("clear page \n" * 100)


def submitUsername(un):  # writes username into save
    global name
    a = tk.messagebox.askyesno("Confirmation",
                               "Are you sure you want to use '" + un + "' as your username? \n(You can't change this "
                                                                       "later!)")
    if a:
        name = str(un)  # set name to argument "un"
        XPFINDR = open("saveData.txt", "w")
        XPFINDR.write(str(rank) + "\n" + name + "\n" + "true")
        XPFINDR.close()  # saves username
        simp()
    else:
        username()


def ranked(s):
    pass


def single(rankorno):
    if rankorno:
        a = tk.messagebox.askyesno("RANKED NOTICE",
                                   "You are playing RANKED 99. If you leave you will receive a penalty!! No to "
                                   "cancel!\n Tip: Un-check "
                                   "ranked to play casual")
        if a:
            displaycardsperperson(">", 3)
            cardSetup()
        else:
            simp()
    else:
        displaycardsperperson(">", 3)
        cardSetup()


def premultiii(rankedorno):
    a = tk.Label(window, text="Host a game or join a game?", font=('charter', 30), bg='cyan',
                 fg='black')  # username text
    a.place(x=400, y=150, anchor=tk.CENTER)
    hostbtn = tk.Button(text='Host', width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
        preH(), destroyBTN(a, hostbtn, nostbtn, 0)])  # submit button
    hostbtn.place(x=300, y=285)  # submit button place
    nostbtn = tk.Button(text='Join', width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
        preN(), destroyBTN(a, hostbtn, nostbtn, 0)])  # submit button
    nostbtn.place(x=500, y=285)  # submit button place


def premulti(rankorno):
    if rankorno:
        a = tk.messagebox.askyesno("RANKED NOTICE",
                                   'You are playing RANKED 99. If you leave you will receive a penalty!! No to '
                                   'cancel!\n Tip: Un-check '
                                   'ranked to play casual')
        if a:
            premultiii(rankorno)
        else:
            simp()
    else:
        premultiii(rankorno)


def simp():  # single player or mp
    a = tk.Label(window, text="Mode Selection", font=('charter', 30), bg='cyan', fg='black')  # username text
    a.place(x=400, y=150, anchor=tk.CENTER)
    rankedtext = tk.Label(window, text=(
            "Rank: " + rankchecklevel(1, rank, 0) + "\nXp: " + str(rank) + "\nXp from " + rankchecklevel(1, rank,
                                                                                                         2) + ": " + str(
        rankchecklevel(1, rank, 1))), font=('charter', 10), bg='cyan',
                          fg='black')  # username text
    rankedtext.place(x=20, y=200)
    rankedornotasf = tk.IntVar()
    rankedcheckboxthing = tk.Checkbutton(window, highlightbackground='#00FFFF', bg='#00FFFF', var=rankedornotasf,
                                         text="Ranked?")
    rankedcheckboxthing.place(x=150, y=300, anchor=tk.CENTER)
    Sp = tk.Button(window, text="Singleplayer", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                   # make single player
                   command=lambda: [destroyBTN(Sp, rankedcheckboxthing, Mp, a),
                                    destroyBTN(rankedtext, 0, 0, 0),
                                    single(rankedornotasf.get())])  # link to singleplayer
    Sp.place(x=300, y=300, anchor=tk.CENTER)
    Mp = tk.Button(window, text="Multiplayer", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                   # make multi player
                   command=lambda: [destroyBTN(Sp, rankedcheckboxthing, Mp, a), destroyBTN(rankedtext, 0, 0, 0),
                                    premulti(rankedornotasf.get())])  # link to mp
    Mp.place(x=500, y=300, anchor=tk.CENTER)


def username():  # username prompt
    a = tk.Label(window, text="Username", font=('charter', 30), bg='cyan', fg='black')  # username text
    a.place(x=400, y=150, anchor=tk.CENTER)
    entry1 = tk.Entry(window)  # make window for input
    entry1.place(x=400, y=300, anchor=tk.CENTER)  # anchor input box
    savetousername = tk.Button(text='Submit', highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
        submitUsername(entry1.get()), destroyBTN(a, entry1, savetousername, 0)])  # submit button
    savetousername.place(x=475, y=285)  # submit button place


def rankchecklevel(print, ranka, calculate):  # check what rank you are with your rank scoer
    global ranks  # all the rank array
    global rankscore  # score you need to get to rank
    global rank  # your rank (number)
    R = 0  # which rank (in order from 0 - 9)
    if 0 <= ranka < 250:  # rank requirements
        R = 0  # set spot in ranked list
        ranka = ranks[0]  # set ranka (which rank you are in text) to the 0st place of the array; bronze
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
    if print and calculate == 0:  # print current rank name
        return ranka
    if calculate == 1:  # for calculations after every game (how many points until next rank)
        if R < 9:
            calculations = rankscore[R] - rank
        else:
            calculations = 0
        return calculations
    if calculate == 2:  # for calculations after every game (name of next rank)
        if R < 9:
            ranka = ranks[R + 1]
        else:
            ranka = "None"
        return ranka


# ranked
def destroySave(d):
    a = tk.messagebox.askyesno("CONFIRM DELETION",
                               "ARE YOU SURE YOU WANT TO DELETE THIS SAVE?(IT'LL BE GONE FOR A LONG LONG TIME)!")  # popup asking if thye will confirm delete
    if a:  # if user responds yes in message box
        try:  # try to remove the file
            os.remove("saveData.txt")
            msg = messagebox.showinfo("Success", "save deleted!")  # if it deletes
        except:  # if it is open in another application
            msg = messagebox.showinfo("Critical Error", "Could Not Delete File. It is open in another app")
        load()

    else:
        asdf = tk.messagebox.showinfo("ERROR",
                                      "USER CANCELLED DELETION. SAVE CORRUPTED.")
        if d == 1:
            load()
        else:
            buttonifySuccess()


def buttonifyFail():  #
    a = tk.messagebox.askyesno("ERROR",
                               "SAVE CORRUPTED. DELETE?")
    if a:  # if user agrees to delete corrupted file
        destroySave(1)
    else:  # if the user cancells the deletion
        # raise SystemExit("COULD NOT LOAD SAVE. SAVE CORRUPTED. CLICK NEW SAVE INSTEAD OF LOAD TO OVERWRITE YOUR SAVE")
        asdf = tk.messagebox.showinfo("ERROR",
                                      "COULD NOT LOAD SAVE SAVE CORRUPTED.")
        load()


def buttonifySuccess():  # if the save loads
    a = tk.Label(window, text=("Save Found! \nINFO:\nRank:" + str(rankchecklevel(1, rank, 0)) + "(" + str(
        rank) + ")\nUsername:" + str(name)), font=('charter', 30), bg='cyan',
                 fg='black')  # print the save informations of the save
    a.place(x=400, y=150, anchor=tk.CENTER)
    ass = tk.Button(window, highlightbackground='#00FFFF', width=20, height=3, bg='#00FFFF', text="Load",
                    # make load button
                    command=lambda: [destroyBTN(ass, a, css, 0), simp()])
    ass.place(x=300, y=300, anchor=tk.CENTER)
    css = tk.Button(window, highlightbackground='#00FFFF', width=20, height=3, bg='#00FFFF', text="Delete",
                    # make delete save button
                    command=lambda: [destroyBTN(ass, a, css, 0), destroySave(0)])
    css.place(x=500, y=300, anchor=tk.CENTER)


def rankedcheck(loadnew):  # loadnew is if it is to make new save or to load the save
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
                    if completed == "false":
                        Sbb = tk.Button(window, highlightbackground='#00FFFF', bg='#00FFFF',
                                        text="[RANKED PENALTY] \n YOU LEFT A GAME: -10 XP\n Click To Continue",
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
        else:
            a = tk.messagebox.showinfo("Aborted",
                                       "Save creation cancelled!")
            load()


def isOverAHunnitorno(turnforplayer):
    global sumc
    if sumc < 100:
        turnforplayer += 1
        play(turnforplayer % 2)
        checkforcardempty()
        window.after(1000, isOverAHunnitorno(turnforplayer))


def gofirstornot():
    global MPorSP
    MPorSP = 0
    turnforplayer = 0
    a = True
    # a = tk.messagebox.showinfo("On Noticed", ("Oppoent is: " + botName))  # print the save informations of the save
    if a:
        isOverAHunnitorno(turnforplayer)


def displaycardsperperson(updown, number):
    global cardn
    global confirmcards
    global bcard
    global pcard
    if updown == "<":
        if cardn > 1:
            cardn -= number
        a = tk.Label(window, text=cardn, highlightbackground='#FFFFFF', font=('charter', 30), bg='#FFFFFF',
                     fg='black')  #
        a.place(x=400, y=300, anchor=tk.CENTER)
    elif updown == ">":
        if cardn < 9:
            cardn += number
        a = tk.Label(window, text=cardn, highlightbackground='#FFFFFF', font=('charter', 30), bg='#FFFFFF',
                     fg='black')  #
        a.place(x=400, y=300, anchor=tk.CENTER)
    elif updown == "cf":
        confirmcards = True
        for i in range(cardn):  # player
            pcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
        for i in range(cardn):  # bot
            bcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
        gofirstornot()

# game stuff
def cardSetup():
    global cardl
    global cardn
    global pcard
    global bcard
    global confirmcards
    ##ask for amount of cards per player
    a = tk.Label(window, text="How Many Cards Per Player? (1-9)", font=('charter', 30), highlightbackground='#00FFFF',
                 bg='#00FFFF',
                 fg='black')  # print the save informations of the save
    a.place(x=400, y=150, anchor=tk.CENTER)
    ass = tk.Button(window, highlightbackground='#00FFFF', bg='#00FFFF', text=">",  # make load button
                    command=lambda: [displaycardsperperson(">", 1)])
    ass.place(x=500, y=300, anchor=tk.CENTER)
    css = tk.Button(window, highlightbackground='#00FFFF', bg='#00FFFF', text="<",  # make delete save button
                    command=lambda: [displaycardsperperson("<", 1)])
    css.place(x=300, y=300, anchor=tk.CENTER)
    confirmbtn = tk.Button(window, width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF', text="Confirm",
                           # make delete save button
                           command=lambda: [displaycardsperperson("cf", 0), destroyBTN(confirmbtn, css, ass, a)])
    confirmbtn.place(x=400, y=425, anchor=tk.CENTER)
    if confirmcards:
        destroyBTN(ass, a, css, confirmbtn)

    else:
        window.after(1000, cardSetup)
    ##giving cards


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


def portbind(a, noh):
    global port
    port = a
    try:
        port = int(port)
        if 1 <= port <= 65535:
            if noh == 1:
                setupH()
        else:
            msg = messagebox.showinfo("Bad Port", "Port is not a number from 1-65535!")  # if it deletes
            if noh == 1:
                preH()
            else:
                preN()
    except:
        msg = messagebox.showinfo("Bad Port", "Port is not a number from 1-65535!")  # if it deletes
        if noh == 1:
            preH()
        else:
            preN()


def preH():
    a = tk.Label(window, text="Port (To Host On)", font=('charter', 30), bg='cyan', fg='black')  #
    a.place(x=400, y=150, anchor=tk.CENTER)
    portenter = tk.Entry(window)  # make window for input
    portenter.place(x=400, y=300, anchor=tk.CENTER)  # anchor input box
    submitbtn = tk.Button(text='Submit', highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
        portbind(portenter.get(), 1), destroyBTN(a, submitbtn, portenter, 0)])  # submit button
    submitbtn.place(x=475, y=285)  # submit button place


def stopListening():
    global port
    global host
    socket.socket(socket.AF_INET,
                  socket.SOCK_STREAM).connect((host, port))
    communications.close()


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
    print(port)
    communications = socket.socket()
    communications.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    host = get_ip()  # socket stuff
    communications.bind((host, port))
    msg = messagebox.askyesno("Hosting",
                              "Host on:\n" + "IP(Local):\n" + str(host) + "\n IP(Global):\n" + str(
                                  external_ip) + "\n Port: \n" + str(port))
    if msg:
        a = tk.Label(window, text="Waiting for connections...", font=('charter', 30), bg='cyan', fg='black')  #
        a.place(x=400, y=150, anchor=tk.CENTER)
        cancelbtn = tk.Button(text='Cancel', highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
            destroyBTN(a, cancelbtn, 0, 0), stopListening])
        cancelbtn.place(x=400, y=300, anchor=tk.CENTER)
        msg = messagebox.showinfo("Starting",
                                  "click ok to start")
        if msg:
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
                "From HOST, on port: ", str(port), ": game between ", name, " [you] (", host, ")(", external_ip,
                ") and ",
                name1,
                " (", theirIP, ") (", theirEIP, ")\n ================= \n")
            # temptuple1 = ("conversation between ",name," (",host,") and ",name1," (",theirIP,") \n ================= \n")
            temptuple1 = "".join(temptuple1)
            h.write(str(temptuple1))
            h.close()
            clearPg()
            print("successfully connected to game. Your Oppoent:" + name1)
            # adsf
    else:
        preH()


def ipbind(a):
    global theirEIP
    theirEIP = a
    try:
        socket.inet_aton(theirEIP)
    except:
        msg = messagebox.showinfo("Bad IP", "The IP you entered is not an IP. Please try again")  # if it deletes
        preN()
    try:
        setupN()
    except:
        msg = messagebox.showinfo("Bad IP & Port", "The IP & port combo you entered is not hosting a 99 game. Please\n "
                                                   "verify that the machine you are trying to connect to is on \n"
                                                   "MULTIPLAYER and is HOSTING")
        preN()


def preN():
    a = tk.Label(window, text="IP and Port (To Connect To)", font=('charter', 30), bg='cyan', fg='black')  #
    a.place(x=400, y=150, anchor=tk.CENTER)
    b = tk.Label(window, text="IP\nPort", font=('charter', 30), bg='cyan', fg='black')  #
    b.place(x=300, y=290, anchor=tk.CENTER)
    ipenter = tk.Entry(window)  # make window for input
    ipenter.place(x=400, y=275, anchor=tk.CENTER)  # anchor input box
    portenter = tk.Entry(window)  # make window for input
    portenter.place(x=400, y=300, anchor=tk.CENTER)  # anchor input box
    submitbtn = tk.Button(text='Submit', highlightbackground='#00FFFF', bg='#00FFFF', command=lambda: [
        portbind(portenter.get(), 0), ipbind(ipenter.get()),
        destroyBTN(a, submitbtn, portenter, ipenter), destroyBTN(0, 0, 0, b)])  # submit button
    submitbtn.place(x=475, y=285)  # submit button place


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
    ipplaceholder = get_ip()
    communications = socket.socket()
    communications.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # tries to reuse socket
    msg = messagebox.askyesno("Connecting",
                              "Connecting to:\n" + "IP(Their):\n" + str(theirEIP) + "\n Port: \n" + str(port))
    if msg:
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

        print("successfully connected to game. Your Oppoent:" + name1)

    else:
        preN()


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

        print("Game Setup Success!")

        print("\n\n\n")
    else:

        print("waiting for oppoent...")

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

        print("Game Setup Success!")

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
            # a = input('You won!, back to the lobby. \nEnter to Continue')
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
            # a = input('You Lost!, back to the lobby. \nEnter to Continue')


def checkotherstuff():
    global sumc
    global MPorSP
    global xpgained
    if sumc > 99 and MPorSP == 0:
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
        # a = input('You lost, back to the lobby. \nEnter to Continue')
    #    else:
    #       isOverAHunnit(1)
    print('Sum: {}'.format(sumc))


def aysecheck(ayse):
    if ayse:
        return True
    else:
        inpt = input('>Should Ace be 1 or 11?<\n')
        if inpt == '1' or inpt == '11':
            if inpt == '1':
                sumc += 1
                added = 1
            else:
                sumc += 11
                added = 11
            p_replace_card(1)
            ayse = True
        else:
            print('\n!!!ERROR: Input was not 1 or 11\n')
    window.after(100, aysecheck(ayse))


def playcardasplayer(haveplayerd, ins):
    global pcard
    global cardl
    global sumc
    global MPorSP
    global added
    global xpgained
    global communications
    global xp
    # whie True:
    haveplayerd = haveplayerd
    if haveplayerd:
        checkotherstuff()
    else:
        inpt = ins
        if inpt != '':
            if inpt[0] == 'a' or inpt[0] == 'A':  # ace
                if 1 in pcard:
                    haveplayerd = aysecheck()
                    playcardasplayer(haveplayerd, "")
            elif inpt[0] == 'j' or inpt[0] == 'J':
                if len(inpt) > 1:
                    if inpt[1] == 'a' or inpt[1] == 'A':  # jack
                        if 11 in pcard:
                            sumc += 10
                            added = 10
                            p_replace_card(11)
                            haveplayerd = True
                            playcardasplayer(haveplayerd, "")
                    elif inpt[1] == 'o' or inpt[1] == 'O':  # joker
                        if 14 in pcard:
                            sumc = 99
                            added = 1000
                            p_replace_card(14)
                            haveplayerd = True
                            playcardasplayer(haveplayerd, "")
            elif inpt[0] == 'q' or inpt[0] == 'Q':  # queen
                if 12 in pcard:
                    sumc += 10
                    added = 10
                    p_replace_card(12)
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
            elif inpt[0] == 'k' or inpt[0] == 'K':  # king
                if 13 in pcard:
                    sumc = 99
                    added = 1000
                    p_replace_card(13)
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
            elif inpt in nums:
                inpt = int(inpt)
                if inpt == 4:  # 4
                    p_replace_card(4)
                    added = 0
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
                elif inpt == 9:  # 9
                    p_replace_card(9)
                    added = 0
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
                elif inpt == 10:  # 10
                    sumc -= 10
                    p_replace_card(10)
                    added = -10
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
                else:  # other numbers
                    sumc += inpt
                    added = inpt
                    p_replace_card(inpt)
                    haveplayerd = True
                    playcardasplayer(haveplayerd, "")
        t = threading.Thread(target=playcardasplayer(), args=(haveplayerd, ""))
        t.start()
        if haveplayerd == True:
            t.join()


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
    #  
    #print("Your Cards: ")
    i = 0
    for i in pcard:  # print cards
        i = int(i)
        if i == 1:
            a = tk.Label(window, text="[Ayce]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=200, y=150, anchor=tk.CENTER)
            # print('[A]', end='')
        elif i == 11:
            a = tk.Label(window, text="[Jack]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=130, y=150, anchor=tk.CENTER)
        elif i == 12:
            a = tk.Label(window, text="[Queen]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=100, y=150, anchor=tk.CENTER)
        elif i == 13:
            a = tk.Label(window, text="[KING]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=70, y=150, anchor=tk.CENTER)
        elif i == 14:
            a = tk.Label(window, text="[JOKER]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=40, y=150, anchor=tk.CENTER)
        else:
            a = tk.Label(window, text="[" + str(i) + "]", font=('charter', 30), bg='cyan', fg='black')  #
            a.place(x=10, y=150, anchor=tk.CENTER)
            # print(type(pcard[i]))
    #asdfdsadsffd = tk.messagebox.showinfo("bum", "cheek")
    asdf = tk.Button(window, text="Play", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                     command=lambda: [destroyBTN(a, 0, asdf, 0), playcardasplayer(False, i)])


def whilereplacementpower(asdfasdfasdf):
    global bcard
    global cardl
    global sumc
    global cardn
    global xpgained
    global xp
    global nums
    global u
    print(sumc)
    power = bcard[random.randint(0, cardn - 1)]
    asdfasdfasdf = asdfasdfasdf
    if power in nums:
        sumc += power
        a = tk.Label(window, text=(botName + " played: " + str(power) + "\n Sum: " + str(sumc)),
                     font=('charter', 30), bg='cyan',
                     fg='black')  #
        a.place(x=400, y=150, anchor=tk.CENTER)
        asdfasdfasdf = True
    if asdfasdfasdf == False:
        g = threading.Thread(target=whilereplacementpower, kwargs=asdfasdfasdf)
    else:
        g.join()
        u = power
    # print('{} played: {}\nSum: {}'.format(botName, power, sumc))


##bot plays
def bot():  # push now but bug here
    global bcard
    global cardl
    global sumc
    global cardn
    global xpgained
    global u
    global xp
    nums = [2, 3, 5, 6, 7, 8]
    power = True  # does the bot have all power cards?
    a = tk.Label(window, text=(""),
                 font=('charter', 30),
                 bg='cyan',
                 fg='black')
    if sumc <= 88:
        for i in bcard:
            if i in nums:
                power = False
                break
        if not power:
            whilereplacementpower(False)
            sumc+=u
        else:
            power = bcard[random.randint(0, cardn - 1)]
            if power == 1:
                inpt = random.randint(1, 2)
                if inpt == 1:
                    sumc += 1
                    a = tk.Label(window, text=(botName + " played: Ayce(1) \n Sum: " + str(sumc)), font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
                else:
                    sumc += 11
                    a = tk.Label(window, text=(botName + " played: Ayce(11) \n Sum: " + str(sumc)),
                                 font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
            else:
                if power == 10:
                    sumc -= 10
                    a = tk.Label(window, text=(botName + " played: 10(-10) \n Sum: " + str(sumc)), font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
                    # print('{} played: 10\nSum: {}'.format(botName, sumc))
                elif power == 11 or power == 12:
                    sumc += 10
                    if power == 11:
                        a = tk.Label(window, text=(botName + " played: Jack(+10) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: J\nSum: {}'.format(botName, sumc))
                    else:
                        a = tk.Label(window, text=(botName + " played: Queen(+10) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: Q\nSum: {}'.format(botName, sumc))
                else:
                    sumc = 99
                    if power == 13:
                        a = tk.Label(window, text=(botName + " played: KING!(=99) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: K\nSum: {}'.format(botName, sumc))
                    else:
                        a = tk.Label(window, text=(botName + " played: Joker!(=99) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: Joker\nSum: {}'.format(botName, sumc))
        b_replace_card(power)
    else:
        played = False  # did bot play yet?
        for i in bcard:
            if i in nums and i + sumc <= 99:
                sumc += i
                a = tk.Label(window, text=(botName + " played: " + str(i) + " \n Sum: " + str(sumc)),
                             font=('charter', 30),
                             bg='cyan',
                             fg='black')  #
                a.place(x=400, y=150, anchor=tk.CENTER)
                # print('{} played: {}\nSum: {}'.format(botName, i, sumc))
                played = True
        if not played:
            if sumc + 10 <= 99:
                if 11 in bcard or 12 in bcard:
                    sumc += 10
                    if 11 in bcard:
                        i = 11
                        a = tk.Label(window, text=(botName + " played: Jack(+10) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: J\nSum: {}'.format(botName, sumc))
                    else:
                        i = 12
                        a = tk.Label(window, text=(botName + " played: Queen(+10) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                    played = True
        if not played:
            if 1 in bcard and sumc < 99:
                sumc += 1
                a = tk.Label(window, text=(botName + " played: Ayce(1) \n Sum: " + str(sumc)), font=('charter', 30),
                             bg='cyan',
                             fg='black')  #
                a.place(x=400, y=150, anchor=tk.CENTER)
                # print('{} played: A(1)\nSum: {}'.format(botName, sumc))
            else:
                if 13 in bcard or 14 in bcard:
                    sumc = 99
                    if 13 in bcard:
                        i = 13
                        a = tk.Label(window, text=(botName + " played: KING(=99) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                        # print('{} played: K\nSum: {}'.format(botName, sumc))
                    else:
                        i = 14
                        a = tk.Label(window, text=(botName + " played: JOKER(=99) \n Sum: " + str(sumc)),
                                     font=('charter', 30),
                                     bg='cyan',
                                     fg='black')  #
                        a.place(x=400, y=150, anchor=tk.CENTER)
                elif 4 in bcard:
                    i = 4
                    a = tk.Label(window, text=(botName + " played: 4(+0) \n Sum: " + str(sumc)),
                                 font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
                elif 9 in bcard:
                    i = 9
                    a = tk.Label(window, text=(botName + " played: 9(+0) \n Sum: " + str(sumc)),
                                 font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
                elif 10 in bcard:
                    sumc -= 10
                    i = 10
                    a = tk.Label(window, text=(botName + " played: 10(-10) \n Sum: " + str(sumc)),
                                 font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
                else:
                    a = tk.Label(window, text=(botName + " YOU WIN: Bot cards:\n"),
                                 font=('charter', 30),
                                 bg='cyan',
                                 fg='black')  #
                    a.place(x=400, y=150, anchor=tk.CENTER)
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
                    # a = input('You won!, back to the lobby. \nEnter to Continue')
                    sumc = 103  # stops bugging th eprogram and keep the game going evne you win
        b_replace_card(i)
    alkjkk = tk.messagebox.showinfo("a""okrrrrrr")
    a.destroy()


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


# pre game set ups
window.geometry("800x600")


def selectMode():
    S = tk.Button(window, text="SinglePlayer", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                  command=lambda: [rankedcheck(), destroyBTN(M, 0, S, 0)])
    S.place(x=160, y=80)
    M = tk.Button(window, text="MultiPlayer", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                  command=lambda: [rankedcheck(), destroyBTN(M, 0, S, 0)])
    M.place(x=240, y=80)


def load():
    a = tk.Label(window, text="Saves", font=('charter', 30), bg='cyan', fg='black')
    a.place(x=400, y=150, anchor=tk.CENTER)
    L = tk.Button(window, text="Load Save", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                  command=lambda: [rankedcheck(0), destroyBTN(La, L, a, 0)])
    L.place(x=300, y=300, anchor=tk.CENTER)
    La = tk.Button(window, text="New Save", width=20, height=3, highlightbackground='#00FFFF', bg='#00FFFF',
                   command=lambda: [rankedcheck(1), destroyBTN(L, La, a, 0)])
    La.place(x=500, y=300, anchor=tk.CENTER)


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
                           "the sum would be 9\n\n There are special cards in this game \nCard values:\nA: 1 or 11 ("
                           "your choice)\n2: 2\n3: 3\n4: 0\n5: "
                           "5\n6: 6\n7: 7\n8: 8\n9: 0\n10: -10\nJ: 10\nQ: 10\nK: Automatically to 99\nJoker: "
                           "Automatically to 99\n\n\n\n\n\n\n\nCLICK HERE TO CONTINUE"
                      , highlightbackground='#00FFFF', bg='#00FFFF', width=800, height=600,
                      command=lambda: [destroyBTN(N, 0, 0, 0), load()])
        N.place(x=400, y=300, anchor=tk.CENTER)


def main():
    A = tk.Button(window, text="Tutorial", width=20, height=3, bg='#00FFFF', highlightbackground='#00FFFF',
                  command=lambda: [tutorial(0), destroyBTN(A, a, V, assss)])
    A.place(x=200, y=400)
    V = tk.Button(window, highlightbackground='#00FFFF', bg='#00FFFF', text="Start", width=20, height=3,
                  command=lambda: [load(), destroyBTN(A, V, a, assss)])
    V.place(x=400, y=400)
    # deckninetynine = Image.open("title.png")
    # deckninetynine = ImageTk.PhotoImage(deckninetynine)
    # deckninetynine = tk.Label(image=deckninetynine)
    # window.create_image(20, 20, anchor=tk.CENTER, image=deckninetynine)


'''whie True:
    # XPFINDR = open("saveData.txt", "w")
    #    bcd = rank + xp
    # XPFINDR.write(str(bcd) + "" + name + "true")
    # XPFINDR.close()
    ##filling cardl
    
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
    # MP or DOM
    clearPg()
    if inpt != '':
        inpt = inpt[0]  # setting input to first letter if input is not enter
    
    if inpt == '2':
        MPorSP = 1
         
        print("[1]Host or [2]Nost?")
         
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
    
    elif inpt == 'x':
        if xpgained > 0:
            raise SystemExit("Successfully Exited. You have earned " + str(xpgained) + " XP Today. Well Done")
        else:
            raise SystemExit("Successfully Exited. You have lost " + str(xpgained) + " XP Today. Better Luck Next Time")
    elif inpt == '1':
        cardSetup()
    
    # gameplay
    if MPorSP == 0:
        # XPFINDR = open("saveData.txt", "w")
        # XPFINDR.write(str(rank) + "" + name + "false")
        # XPFINDR.close()
        clearPg()
         
        print("Do you want to go first?")
         
        inpt = input('>>>')  # add difficulties later
        clearPg()
        if inpt != '':
            inpt = inpt[0]
        if inpt == 'y' or inpt == 'Y':
            inpt = 0
        else:
            inpt = 1
        clearPg()
         
        print("Oppoent is: " + botName)
        whie sumc < 100:
            inpt += 1
            play(inpt % 2)
            checkforcardempty()
        clearPg()
    else:
        # XPFINDR = open("saveData.txt", "w")
        # XPFINDR.write(str(rank) +  + name + "false")
        # XPFINDR.close()
        whie sumc < 100:
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
            '''
if __name__ == '__main__':
    main()
    window.mainloop()
