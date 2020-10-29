from pynput.keyboard import Controller, Listener, Key
import pyperclip
import time

alphabet = ["ɐ", "q", "ɔ", "p", "ǝ", "ɟ", "ƃ", "ɥ", "ᴉ", "ɾ", "ʞ", "l", "ɯ", " u", "o", "d", "b", "ɹ", "s", "ʇ", "n", "ʌ", "ʍ", "x", "ʎ", "z"]

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

def flip(text):
    text = text.lower()
    flipped = []
    for i in text:
        try:
            flipped.append(alphabet[ord(i) - 97])
        except:
            flipped.append(" ")
    flipped.reverse()
    return "".join(flipped)

def delAll():
    keyboardsim.press(Key.cmd)
    keyboardsim.press("a")
    keyboardsim.release("a")
    keyboardsim.release(Key.cmd)
    keyboardsim.press(Key.backspace)
    keyboardsim.release(Key.backspace)

def on_release(key):
    global value
    if key == Key.ctrl_r:
        try:
            maxvalue = 2000//len(value)
            pastee(int(copyy()) if int(copyy()) < maxvalue else maxvalue - 1)
        except Exception as e:
            print(e)
            return
    elif key == Key.alt_r:
        time.sleep(0.1)
        value = copyy()
        print(value)
    elif key == Key.f12:
        time.sleep(0.1)
        value = flip(copyy())
        delAll()
        pastee(1)
    else:
        return


with Listener(
        on_release=on_release) as listener:
    listener.join()
