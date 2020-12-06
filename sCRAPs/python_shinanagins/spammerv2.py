from pynput.keyboard import Controller, Listener, Key

# version 0.2
print('r-cmd/right-ctrl to start cheet')
keyboardsim = Controller()


def on_press(key):
    keyboardsim.type("Check your attic before you sleep tonight <3")
    #keyboardsim.type("\n")


with Listener(
        on_press=on_press) as listener:
    listener.join()
