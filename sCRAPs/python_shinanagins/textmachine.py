from pynput.keyboard import Controller, Listener, Key, KeyCode
import pyperclip
import time

alphabet = ["ɐ", "q", "ɔ", "p", "ǝ", "ɟ", "ƃ", "ɥ", "ᴉ", "ɾ", "ʞ", "l", "ɯ", " u", "o", "d", "b", "ɹ", "s", "ʇ", "n", "ʌ", "ʍ", "x", "ʎ", "z"]
emojibet = ["🇦", "🇧", "🇨", "🇩", "🇪", "🇫", "🇬", "🇭", "🇮", "🇯", "🇰", "🇱", "🇲", "🇳", " 🇴", "🇵", "🇶", "🇷", "🇸", "🇹", "🇺", "🇻", "🇼", "🇽", "🇾", "🇿"]

# how to setup your keyboard bc for control and whateves keys
keyboardsim = Controller()
value = None
spaceToggle = False
isShortcut = False

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

def emojize(text):
    text = text.lower()
    flipped = []
    for i in text:
        try:
            flipped.append(emojibet[ord(i) - 97].decode())
        except:
            flipped.append(" ")
    return "".join(flipped)

def delAll():
    keyboardsim.press(Key.cmd)
    keyboardsim.press("a")
    keyboardsim.release("a")
    keyboardsim.release(Key.cmd)
    keyboardsim.press(Key.backspace)
    keyboardsim.release(Key.backspace)

def spacer(key):
    global spaceToggle
    global isShortcut

    if key == KeyCode.from_char('s') and isShortcut:
        spaceToggle = True
        isShortcut = False  
    elif key == Key.backspace and spaceToggle and not isShortcut:
        return
    elif key != Key.space and spaceToggle and not isShortcut:
        keyboardsim.type(" ")

def fliporno(key):
    global value
    global isShortcut

    if key == KeyCode.from_char('f') and isShortcut:
        time.sleep(0.1)
        value = flip(copyy())
        delAll()
        pastee(1)
        isShortcut = False
    else:
        return

def emojiorno(key):
    global value
    global isShortcut

    if key == KeyCode.from_char('e') and isShortcut:
        time.sleep(0.1)
        value = emojize(copyy())
        delAll()
        pastee(1)
        isShortcut = False
    else:
        return

'''try:
        maxvalue = 2000//len(value)
        pastee(int(copyy()) if int(copyy()) < maxvalue else maxvalue - 1)
    except Exception as e:
        print(e)
        return
        time.sleep(0.1)
        value = copyy()
'''

def on_press(key):
    global spaceToggle
    global value
    global isShortcut

    if key == Key.f12:
        print(isShortcut)
        isShortcut = not isShortcut
        spaceToggle = False
    
    spacer(key)
    fliporno(key)
    emojiorno(key)

with Listener(
        on_press=on_press) as listener:
    listener.join()
