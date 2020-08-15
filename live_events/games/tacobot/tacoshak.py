import string
import random
import time
import math as albreto
import os
from pynput.keyboard import Controller, Listener, Key

#version 0.2
print('r-cmd to start cheet')
alphabet = list(string.ascii_uppercase)
keyboardsim = Controller()
command = [  # y=0, y=1
    ["tips\n", 300],  # 5 min x=1
    ["work\n", 600],  # 10 min x=2
    ["clean\n", 86400],  # one day in seconds x=3
    ["daily\n", 86400],  # x=4
]
botconfusion = []
with open('distract.txt', 'r') as b:
    for line in b:
        botconfusion.append(line[:-1])
#thanks botmooo for project 495


def start(timetoadd):
    dayfromnow = 86400
    while True:
        counter = 1
        i = counter % 2
        timewait = 300
        randomdivision = random.randint(1, 40)
        if i != 0:
            timewait = albreto.ceil((((command[i][1] - command[i - 1][1]) + random.randint(10,
                                                                                           1200)) + timetoadd) / randomdivision)  # random delay from 10seconds to 12 minutes to confirm anti-bot
        print(timewait*randomdivision)
        for distractlesgo in range(randomdivision):
            keyboardsim.type(str(botconfusion[random.randint(0, len(botconfusion) - 1)])+"\n")
            time.sleep(timewait)
        dayfromnow -= timewait * randomdivision
        keyboardsim.type("%" + command[i][0])
        if dayfromnow <= 0:
            time.sleep(random.randint(5, 10))
            keyboardsim.type("%" + command[2][0])
            time.sleep(random.randint(5, 20))
            keyboardsim.type("%" + command[3][0])
            dayfromnow = 86400
        counter += 1


def on_press(key):  # using cmd and ctrl bc they cant be repeated (smort)
    print("key pressed" + str(key))
    if key == Key.cmd_r or key == Key.ctrl_r:
        print("starting... in 10-50 seconds")
        a = 0
        for i in range(0, len(command)):
            a = random.randint(10, 49)
            time.sleep(a)
            keyboardsim.type("%" + command[i][0])
        start(a)
        # pass


def on_release(key):
    print("key release" + str(key))
    if key == Key.esc:
        return False  # kills listener


with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
