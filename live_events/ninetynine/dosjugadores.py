# imports
import random
import socket
import sys
import datetime
import time
import urllib.request
import os

# files:


external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8')  # Global ip
name = input("Username?\n")
name1 = ""  # oppoent name
conn = ''  # host send
port = 12345  # def
theirEIP = ""
host = ""
MPorSP = 0  # 1 is mp 0 is sp
# vars (game)
cardl = []  # cards left
sumc = 0  # sum of cards
cardn = 0  # amount of cards per player
pcard = []  # player cards
inpt = ''  # input
nums = ['2', '3', '4', '5', '6', '7', '8', '9', '10']  # number cards
# single player
botNames = ["SoccerMom", "PlasticFoods", "BustedKneeCap", "gitPushOrca", "godlyPro"]
bcard = []  # bot cards
# multi player
turn = 0


# game stuff
def cardSetup():
    global cardl
    global cardn
    global pcard
    global bcard
    ##ask for amount of cards per player
    if inpt != 1:
        while True:
            cardn = input('How many cards per player? (1 to 10)\n')
            try:  # trying to set input to integer
                cardn = int(cardn)
                if cardn <= 10:
                    break
                print('Input was greater than 10\n')
            except:
                print('Input was not an integer\n')

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
    global name
    global port
    global external_ip
    global name1
    global conn
    global theirEIP
    global turn
    turn = random.randint(0, 1)
    port = int(input("port?"))  # port
    conn = socket.socket()
    conn.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    host = get_ip()  # socket stuff
    conn.bind((host, port))
    print("logged in on local ip:", host)  # print out local ip
    print("\nglobal IP:", external_ip)  # print global ip
    print(port)  # print port for global ip
    print("\nsuccessfully connected \n waiting for connections\n cancel?")
    conn.listen(1)  # wait for ppl to join
    conn, adr = conn.accept()  # if see ppl accept it
    name = name.encode()  # send your name to them
    conn.sendall(name)
    name = name.decode()
    name1 = conn.recv(1024)  # receive their name
    name1 = name1.decode()
    theirIP = conn.recv(1024)  # receive their ip (local)
    theirIP = theirIP.decode()
    print(theirIP)
    theirEIP = conn.recv(1024)  # receive their ip (global)
    theirEIP = theirEIP.decode()
    turn = str(turn).encode()  # send your order of cards to them
    conn.sendall(turn)
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
        "From HOST, on port: ", str(port), ": conversation between ", name, " (", host, ")(", external_ip, ") and ",
        name1,
        " (", theirIP, ") (", theirEIP, ")\n ================= \n")
    # temptuple1 = ("conversation between ",name," (",host,") and ",name1," (",theirIP,") \n ================= \n")
    temptuple1 = "".join(temptuple1)
    h.write(str(temptuple1))
    h.close()
    # os.system('clear')
    print("successfully connected to game. Your Oppoent:" + name1)


def setupN():  # setup for the nonsimpyt nosters
    global name
    global port
    global external_ip
    global name1
    global conn
    global theirEIP
    global turn
    port = int(input("port?"))
    ipplaceholder = get_ip()
    conn = socket.socket()
    conn.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # tries to reuse socket
    print("logged in on local ip:", ipplaceholder)  # local ip
    print("\nglobal IP:", external_ip)  # glob ip
    print(port)  # port
    theirEIP = input(str("please enter host IP of server\n"))  # enter ip to connect to
    conn.connect((theirEIP, port))
    name1 = conn.recv(1024)  # recieve their name
    name1 = name1.decode()
    name = name.encode()  # encode and send ur name
    conn.send(name)
    name = name.decode()  # eecode name after sending
    print(ipplaceholder)
    ipplaceholder = ipplaceholder.encode()  # send local ip
    conn.send(ipplaceholder)
    ipplaceholder = ipplaceholder.decode()
    time.sleep(0.5)
    extern = external_ip.encode()
    conn.send(extern)  # send glob ip
    turn = conn.recv(1024)  # Recv game order
    turn = turn.decode()
    turn = int(turn)
    temptuple = ("Game", str(datetime.datetime.now()), ".txt")
    namething = str("".join(temptuple))
    namething = namething.replace(' ', '_')
    namething = namething.replace(':', '_')
    h = open(namething, "w+")
    temptuple1 = (
        "From NOST, on port: ", str(port), ": conversation between ", name, " (", ipplaceholder, ")(", external_ip,
        ") and ", name1, " (", theirEIP, ") (", theirEIP, ")\n ================= \n")
    temptuple1 = "".join(temptuple1)
    h.write(str(temptuple1))
    h.close()
    print("successfully connected to game. Your Oppoent:" + name1)


def multiplayer():
    global cardl
    global cardn
    global pcard
    global bcard
    global conn
    if turn == 1:
        cardSetup()
        conn.sendall(cardn.encode())
        for i in range(cardn):
            pcard[i] = pcard[i].encode()
            conn.sendall(pcard[i])
            pcard[i] = pcard[i].decode()
        for i in range(cardn):
            bcard[i] = bcard[i].encode()
            conn.sendall(bcard[i])
            bcard[i] = bcard[i].decode()
        for i in range(len(cardl) - cardn):
            cardl[i] = cardl[i].encode()
            conn.sendall(cardl[i])
            cardl[i] = cardl[i].decode()
    else:
        print("waiting for oppoent...")
        cardn = conn.recv(1024)
        cardn = cardn.decode()
        pcard = [0] * cardn  # fucc u out of bound error raaa
        bcard = [0] * cardn
        cardl = [0] * cardn
        for i in range(cardn):
            pcard[i] = conn.recv(1024)
            pcard[i] = pcard[i].decode()  # recv card lists
        for i in range(cardn):
            pcard[i] = conn.recv(1024)
            bcard[i] = bcard[i].decode()
        for i in range(cardn):
            cardl[i] = conn.recv(1024)
            cardl[i] = cardl[i].decode()


# pre game set ups
##filling cardl
for i in range(1, 14):
    for k in range(4):
        cardl.append(i)
for i in range(2):
    cardl.append(14)

botName = botNames[random.randint(0, 4)]
##ask if it is first time playing
inpt = input('Is this your first time playing 99?\n')
if inpt != '':
    inpt = inpt[0]  # setting input to first letter if input is not enter
if inpt == 'y' or inpt == 'Y':  # need tutorial
    inpt = input(
        'Objective of game: Get to 99 but don\'t go over. Make the other person go over 99 to win\n\nHow to play: '
        'When you play a card it adds to the sum of all the cards. For example if the first card played was 6 and the '
        'second card played was 3, the sum would be 9\n\nCard values:\nA: 1 or 11 (your choice)\n2: 2\n3: 3\n4: 0\n5: '
        '5\n6: 6\n7: 7\n8: 8\n9: 0\n10: -10\nJ: 10\nQ: 10\nK: Automatically to 99\nJoker: Automatically to '
        '99\n\nEnter to continue:\n')  # print tutorial

# MP or DOM
inpt = input('[1]Singleplayer or [2]IP Play?\n')
if inpt != '':
    inpt = inpt[0]  # setting input to first letter if input is not enter
if inpt == '2':
    MPorSP = 1
    inpt = input('[1]Host or [2]Nost? (free subscription of ISIMPYT if you choose 1)\n')
    if inpt != '':
        inpt = inpt[0]  # setting input to first letter if input is not enter
    if inpt == '1':
        setupH()  # setupMPshenanananannanannananangans
    elif inpt == '2':
        setupN()  # setupMP NOST HAHAHHAHA NOSTING U KIDDING ME IDOT I TOLD U U GET FREE ISIMPYT SUBIF U GET HOST SDJGHLSKJFJKLDKLJFLH
    multiplayer()
    print("works")
else:
    cardSetup()


# user def functions
##player replace card
def p_replace_card(c):
    global pcard
    count = -1
    for i in pcard:
        count += 1
        if i == c:
            pcard.pop(count)
            pcard.append(cardl.pop(random.randint(0, len(cardl) - 1)))
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


##player plays
def player():
    global pcard
    global cardl
    global sumc
    global MPorSP
    print("Your Cards: ")
    for i in pcard:  # print cards
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
    while True:
        inpt = input('\n\nChoose a card to play:\n')
        if inpt != '':
            if inpt[0] == 'a' or inpt[0] == 'A':  # ace
                if 1 in pcard:
                    while True:
                        inpt = input('Should Ace be 1 or 11?\n')
                        if inpt == '1' or inpt == '11':
                            if inpt == '1':
                                sumc += 1
                            else:
                                sumc += 11
                            p_replace_card(1)
                            break
                        else:
                            print('\nInput was not 1 or 11\n')
                    break
            elif inpt[0] == 'j' or inpt[0] == 'J':
                if len(inpt) > 1:
                    if inpt[1] == 'a' or inpt[1] == 'A':  # jack
                        if 11 in pcard:
                            sumc += 10
                            p_replace_card(11)
                            break
                    elif inpt[1] == 'o' or inpt[1] == 'O':  # joker
                        if 14 in pcard:
                            sumc = 99
                            p_replace_card(14)
                            break
            elif inpt[0] == 'q' or inpt[0] == 'Q':  # queen
                if 12 in pcard:
                    sumc += 10
                    p_replace_card(12)
                    break
            elif inpt[0] == 'k' or inpt[0] == 'K':  # king
                if 13 in pcard:
                    sumc = 99
                    p_replace_card(13)
                    break
            elif inpt in nums:
                inpt = int(inpt)
                if inpt == 4:  # 4
                    p_replace_card(4)
                    break
                elif inpt == 9:  # 9
                    p_replace_card(9)
                    break
                elif inpt == 10:  # 10
                    sumc -= 10
                    p_replace_card(10)
                    break
                else:  # other numbers
                    sumc += inpt
                    p_replace_card(inpt)
                    break
    if MPorSP == 1:
        inpt = inpt.encode()
        conn.send(inpt)  # send card played
    if sumc > 99:
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
        raise SystemExit('\n\nYou lose')
    print('Sum: {}'.format(sumc))


##bot plays
def bot():
    global bcard
    global cardl
    global sumc
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
                    print('===========\n {} played: {}\nSum: {}\n'.format(botName, power, sumc))
                    break
        else:
            power = bcard[random.randint(0, cardn - 1)]
            if power == 1:
                inpt = random.randint(1, 2)
                if inpt == 1:
                    sumc += 1
                    print('Card played: A(1)\nSum: {}\n'.format(sumc))
                else:
                    sumc += 11
                    print('Card played: A(11)\nSum: {}\n'.format(sumc))
            else:
                if power == 10:
                    sumc -= 10
                    print('Card played: 10\nSum: {}\n'.format(sumc))
                elif power == 11 or power == 12:
                    sumc += 10
                    if power == 11:
                        print('Card played: J\nSum: {}\n'.format(sumc))
                    else:
                        print('Card played: Q\nSum: {}\n'.format(sumc))
                else:
                    sumc = 99
                    if power == 13:
                        print('Card played: K\nSum: {}\n'.format(sumc))
                    else:
                        print('Card played: Joker\nSum: {}\n'.format(sumc))
        b_replace_card(power)
    else:
        played = False  # did bot play yet?
        for i in bcard:
            if i in nums and i + sumc <= 99:
                sumc += i
                print('Card played: {}\nSum: {}\n'.format(i, sumc))
                played = True
        if not played:
            if sumc + 10 <= 99:
                if 11 in bcard or 12 in bcard:
                    sumc += 10
                    if 11 in bcard:
                        i = 11
                        print('Card played: J\nSum: {}\n'.format(sumc))
                    else:
                        i = 12
                        print('Card played: Q\nSum: {}\n'.format(sumc))
                    played = True
        if not played:
            if 1 in bcard and sumc < 99:
                sumc += 1
                print('Card played: A(1)\nSum: {}\n'.format(sumc))
            else:
                if 13 in bcard or 14 in bcard:
                    sumc = 99
                    if 13 in bcard:
                        i = 13
                        print('Card played: K\nSum: {}\n'.format(sumc))
                    else:
                        i = 14
                        print('Card played: Joker\nSum: {}\n'.format(sumc))
                elif 4 in bcard:
                    i = 4
                    print('Card played: 4\nSum: {}\n'.format(sumc))
                elif 9 in bcard:
                    i = 9
                    print('Card played: 9\nSum: {}\n'.format(sumc))
                elif 10 in bcard:
                    sumc -= 10
                    i = 10
                    print('Card played: 10\nSum: {}\n'.format(sumc))
                else:
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
                    raise SystemExit('\n\nYou win!')
        b_replace_card(i)


##turn test
def play(n):
    if n == 0:
        bot()
    else:
        player()


# gameplay
inpt = input('Do you want to go first?\n')  # add difficulties later
if inpt != '':
    inpt = inpt[0]
if inpt == 'y' or inpt == 'Y':
    inpt = 0
else:
    inpt = 1
print("Oppoent is: " + botName)
while True:
    inpt += 1
    play(inpt % 2)
    if cardl == []:  # if cards all used up recycle deck
        for i in range(1, 14):  # TODO work on making recycled deck not have duplicates
            for k in range(4):
                cardl.append(i)
        for i in range(2):
            cardl.append(14)
