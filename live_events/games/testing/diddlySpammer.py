import pynput
import keyboard
from pynput.keyboard import Key, Controller

dict = {

}
keyboardsim = Controller()
while True:
    if keyboard.is_pressed('q'):
        #for i in range(1000):
        keyboardsim.type("\n")
