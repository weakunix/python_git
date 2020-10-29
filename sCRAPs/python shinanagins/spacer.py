from pynput.keyboard import Controller, Listener, Key

keyboardsim = Controller()

toggle = True

def on_press(key):
    global toggle
    if key == Key.cmd_l or key == Key.ctrl_l:
        if toggle:
            toggle = False
        else:
            toggle = True
    elif key == Key.backspace:
        return
    elif key != Key.space and toggle:
        keyboardsim.type(" ")
    else:
        return


with Listener(
        on_press=on_press) as listener:
    listener.join()
