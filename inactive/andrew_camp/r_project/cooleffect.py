import turtle, time, random
moo = turtle.Turtle()
cow = turtle.Screen()
'''
cow.colormode(255)
red = random.randint(0, 255)
green = random.randint(0, 255)
blue = random.randint(0, 255)
moo.fillcolor((red, green, blue))
'''
moo.fillcolor('blue')
moo.hideturtle()
for n in range(3, 100):
    cow.tracer(n)
    moo.begin_fill()
    for i in range(n):
        moo.forward(600 / n)
        moo.left(360 / n)
    moo.penup()
    moo.setpos(0, 0)
    moo.pendown()
    for i in range(n):
        moo.forward(600 / n)
        moo.left(-360 / n)
    moo.penup()
    moo.setpos(0, 0)
    moo.pendown()
    for i in range(n):
        moo.forward(-600 / n)
        moo.left(360 / n)
    moo.penup()
    moo.setpos(0, 0)
    moo.pendown()
    for i in range(n):
        moo.forward(-600 / n)
        moo.left(-360 / n)
    moo.penup()
    moo.setpos(0, 0)
    moo.pendown()
cow.mainloop()
