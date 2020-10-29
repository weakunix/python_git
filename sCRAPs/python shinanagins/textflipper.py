from pynput.keyboard import Controller, Listener, Key
import pyperclip
import time

# how to setup your keyboard bc for control and whateves keys
keyboardsim = Controller()
value = None

def copyy():
    keyboardsim.press(Key.cmd)
    keyboardsim.press("a")
    keyboardsim.release("a")
    keyboardsim.release(Key.cmd)
    keyboardsim.press(Key.cmd)
    keyboardsim.press("c")
    keyboardsim.release("c")
    keyboardsim.release(Key.cmd)
    time.sleep(0.1)
    return(str(pyperclip.paste()))

def pastee(times):
    global value
    keyboardsim.type(str(value) * times)
    value = None

def on_release(key):
    global value
    if key == Key.ctrl_r:
        try:
            pastee(int(copyy()) if int(copyy()) < 20 else 20)
        except Exception as e:
            print(e)
            return
    elif key == Key.alt_r:
        time.sleep(0.1)
        value = copyy()
        print(value)
    elif key == Key.f12:
        exit()
    else:
        return


with Listener(
        on_release=on_release) as listener:
    listener.join()
