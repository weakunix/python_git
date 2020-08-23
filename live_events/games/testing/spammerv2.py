from pynput.keyboard import Controller, Listener, Key

# version 0.2
print('r-cmd/right-ctrl to start cheet')
keyboardsim = Controller()


def on_press(key):
    if key == Key.cmd_r or key == Key.ctrl_r:
        for i in range(100):
            keyboardsim.type(str("/cow work"))
            keyboardsim.type("\n")


with Listener(
        on_press=on_press) as listener:
    listener.join()
