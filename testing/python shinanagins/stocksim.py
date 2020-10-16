import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random
import threading
import tkinter as tk

window = tk.Tk()
window.geometry("800x600")
change = random.uniform(-0.2, 0.2)
percentinvestedat = 0


def invest():
    global percentinvestedat
    percentinvestedat = change + value


def pull():
    global percentinvestedat
    gained = (change + value) - percentinvestedat
    print("gained" + str(gained))
    print("Git pullOrcadadle! You have invested in this stock at " + str(percentinvestedat) + "now it is worth" + str(
        (change + value)))


def main():
    b = tk.Button(window, text="Hit it!", command=invest)
    b.place(relx=0.5, rely=0.6)
    c = tk.Button(window, text="I'll stand and retract!", command=pull)
    c.place(relx=0.6, rely=0.6)
    a = tk.Label(window, text="Stalk simulator, numbers change by the second. goodluck investor!")
    a.place(relx=0.5, rely=0.5)
    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()
    window.after(1000, main())


fig = plt.figure()
ax1 = fig.add_subplot(1, 1, 1)
xar = []
yar = []
counter = 0
value = random.randint(1, 100)


def animate(i):
    global xar
    global yar
    global counter
    global value
    global change
    change = random.uniform(-0.2, 0.2)
    if len(xar) >= 10:
        xar.remove(xar[0])
    if len(yar) >= 10:
        yar.remove(yar[0])
    multiplier = random.uniform(1, 2)
    divider = random.uniform(1, 3)
    if random.randint(0, 90) == 11:
        value *= multiplier
    elif random.randint(0, 100) == 11:
        value /= divider
    xar.append(counter)
    yar.append(change + value)
    ax1.clear()
    ax1.plot(xar, yar)
    counter += 1


if __name__ == '__main__':
    main()
    window.mainloop()
