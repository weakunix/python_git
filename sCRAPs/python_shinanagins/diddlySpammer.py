from pynput.keyboard import Controller, Listener, Key
import time

# how to setup your keyboard bc for control and whateves keys
keyboardsim = Controller()


#def on_press(key):
#    if key == Key.cmd_l:
time.sleep(5)

for i in range(100):
    keyboardsim.type("Congratulations! You have won a $1000 amazon giftcard by becoming our lucky buyer. Text YES to confirm\n")


#with Listener(
#        on_press=on_press) as listener:
#    listener.join()