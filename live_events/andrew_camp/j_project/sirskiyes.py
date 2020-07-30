import turtle,time
bob = turtle.Turtle()
screen = turtle.Screen()
screen.setup(800,600)
screen.tracer(2000)
bob.penup()
bob.setpos(-100,-100)
side = 200
bob.left(60)
bob.pendown()
def sir(side,n):
    if n>1:
        for i in range(3):
            bob.forward(side)
            bob.left(-120)
            sir(side/2,n-1)
        else:
            for i in range(3):
                bob.forward(side)
                bob.left(-120)
for i in range (10):
    sir(1800,i)
    screen.update()
    time.sleep(1)
