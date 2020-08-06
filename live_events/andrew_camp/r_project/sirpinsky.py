import turtle, time, random
bob = turtle.Turtle()
screen = turtle.Screen()
screen.setup(650, 650)
screen.tracer(2000)
bob.penup()
bob.setpos(-290, -250)
side = 200
bob.left(60)
bob.pendown()
screen.colormode(255)
def yessirski(side, n):
    if n > 1:
        for i in range(3):
            bob.forward(side)
            red = random.randint(0, 255)
            green = random.randint(0, 255)
            blue = random.randint(0, 255)
            bob.color((red, green, blue))
            bob.left(-120)
            yessirski(side / 2, n - 1)
    else:
        for i in range(3):
            bob.forward(side)
            bob.left(-120)
for i in range(1, 10):
    yessirski(600, i)
    screen.update()
    time.sleep(1)
screen.mainloop()
