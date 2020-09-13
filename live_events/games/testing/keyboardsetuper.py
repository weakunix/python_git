from pynput.keyboard import Controller, Listener

# how to setup your keyboard bc for control and whateves keys
keyboardsim = Controller()


def on_press(key):
    print(key)


with Listener(
        on_press=on_press) as listener:
    listener.join()
