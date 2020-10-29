from pynput.keyboard import Controller, Listener, Key

# how to setup your keyboard bc for control and whateves keys
keyboardsim = Controller()


def on_press(key):
    if key == Key.cmd_l or key == Key.ctrl_l:
        exit()
    elif key == Key.backspace:
        return
    elif key != Key.space:
        keyboardsim.type(" ")
    else:
        return


with Listener(
        on_press=on_press) as listener:
    listener.join()
