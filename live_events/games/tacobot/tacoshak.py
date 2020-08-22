import string
import random
import time
import math as albreto
from pynput.keyboard import Controller, Listener, Key

# version 0.3
print('r-cmd to start cheet')
alphabet = list(string.ascii_uppercase)
keyboardsim = Controller()
command = [  # y=0, y=1
    ["tips\n", 300],  # 5 min x=1
    ["work\n", 600],  # 10 min x=2
    ["clean\n", 86400],  # one day in seconds x=3
    ["daily\n", 86400],  # x=4
    ["overtime\n", 89]
]
botconfusion = []
dayfromnow = (86400 + random.randint(100, 300))
counter = 1
with open('distract.txt', 'r') as b:
    for line in b:
        botconfusion.append(line[:-1])


# thanks botmooo for project 495


def start(timetoadd):
    global counter
    b = open("documentation.txt", "w+")
    b.write("")
    b.close()
    a = open("documentation.txt", "a+")
    randomdivision = 3
    timewait = 120
    print(albreto.ceil(((300 + random.randint(0,
                                                   100)) + timetoadd) / randomdivision))  # random delay from 10seconds to 9 minutes to confirm anti-bot
    timewait = int(timewait)
    print(timewait * randomdivision)
    exampl = 0
    for distractlesgo in range(randomdivision):
        keyboardsim.type(str(botconfusion[random.randint(0, len(botconfusion) - 1)]) + "\n")
        time.sleep(timewait)
        exampl += timewait
    if counter % 2 == 0:
        keyboardsim.type("%" + command[1][0])  # work if it is 10 mins
        time.sleep(random.randint(4, 30))
    keyboardsim.type("%" + command[0][0])  # tips every 5 mins or so
    if counter % 6 == 0:
        time.sleep(random.randint(4, 30))
    counter += 1
    start(0)


def on_press(key):  # using cmd and ctrl bc they cant be repeated (smort)
    print("key pressed" + str(key))
    if key == Key.cmd_r or key == Key.ctrl_r:
        print("starting... in 10-20 seconds")
        for i in range(0, len(command)):
            a = random.randint(10, 20)
            time.sleep(a)
            keyboardsim.type("%" + command[i][0])
        start(0)
        # pass


def on_release(key):
    # print("key release" + str(key))
    if key == Key.esc:
        return False  # kills listener


with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
