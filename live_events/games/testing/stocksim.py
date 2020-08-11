import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random

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
    yar.append(random.uniform(-0.05, 0.05) + value)
    ax1.clear()
    ax1.plot(xar, yar)
    counter += 1


ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
