import string
import keyboard
import random
import time
from pynput.keyboard import Controller

alphabet = list(string.ascii_uppercase)
keyboardsim = Controller()

while True:
    if keyboard.is_pressed('q'):
        for i in range(100):
            a = []
            #for er in range(random.randint(1, 5)):
            #    a.append(alphabet[random.randint(0, len(alphabet) - 1)])
            keyboardsim.type(str("https://github.com/weakunix/python_git"))
            keyboardsim.type("\n")
        break
keyboardsim.type("This was typed using a Python script. How does it feel to get beaten by a bot? ;)\n")