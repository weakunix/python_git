import turtle, time

bob = turtle.Turtle()
bob.fillcolor("blue")
bob.penup()
scream = turtle.Screen()

for n in range (3,100):
    scream.tracer(n)
    bob.begin_fill()
    for i in range (n):
        bob.forward(600/n)
        bob.left(360/n)
    bob.penup()
    bob.setpos(0,0)
    bob.pendown()

    for i in range (n):
        bob.forward(-600/n)
        bob.left(-360/n)
    bob.penup()
    bob.setpos(0,0)
    bob.pendown()

    for i in range (n):
        bob.forward(600/n)
        bob.left(-360/n)
    bob.penup()
    bob.setpos(0,0)
    bob.pendown()

    for i in range (n):
        bob.forward(-600/n)
        bob.left(360/n)

    bob.end_fill()
    scream.update()
    time.sleep(1)
    bob.clear()
