import string
import random
import time
import math as albreto
import os
from pynput.keyboard import Controller, Listener, Key

#version 0.1
print('r-cmd to start cheet')
alphabet = list(string.ascii_uppercase)
keyboardsim = Controller()
command = [  # y=0, y=1
    ["tips\n", 300],  # 5 min x=1
    ["work\n", 600],  # 10 min x=2
    ["clean\n", 86400],  # one day in seconds x=3
    ["daily\n", 86400],  # x=4
]
botconfusion = [
    "What a nice weather!\n",
    "what the frick was that\n",
    "@botmoooo, isn't the naibing big today?\n",
    "if life is bigger than life, what is bigger than it?\n"
]


def start(timetoadd):
    for i in range(0, len(command)):
        timewait = 300
        if i != 0:
            timewait = albreto.ceil((((command[i][1] - command[i - 1][1]) + random.randint(10,
                                                                                           1200)) + timetoadd) / 2)  # random delay from 10seconds to 12 minutes to confirm anti-bot
        print(timewait)
        keyboardsim.type("%" + command[i][0])
        time.sleep(timewait)
        keyboardsim.type(botconfusion[random.randint(0, len(botconfusion))])
        time.sleep(timewait)
        # pass


def on_press(key):  # using cmd and ctrl bc they cant be repeated (smort)
    print("key pressed" + str(key))
    if key == Key.cmd_r or key == Key.ctrl_r:
        a = 0
        for i in range(0, len(command) - 1):
            a = random.randint(2, 49)
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
