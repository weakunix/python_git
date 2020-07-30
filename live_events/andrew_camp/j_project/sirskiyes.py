import turtle,time,random
bob = turtle.Turtle()
screen = turtle.Screen()
screen.setup(800,600)
screen.tracer(2000)
bob.penup()
bob.setpos(-800,-600)
side = 200
bob.left(60)
bob.pendown()
screen.colormode(255)
red = 0
green = 0
blue = 255
def sir(side,n):
    global red
    global blue
    global green
    if n>1:
        for i in range(3):
            bob.forward(side)
            red = random.randint(0,255)
            green = random.randint(0,255)
            blue = random.randint(0,255)
            bob.left(-120)
            sir(side/2,n-1)
        else:
            for i in range(3):
                red = random.randint(0,255)
                green = random.randint(0,255)
                blue = random.randint(0,255)
                bob.left(-120)
                sir(side/2,n-1)
                bob.forward(side)
                bob.left(-120)
for i in range (10):
    sir(1800,i)
    screen.update()
    time.sleep(1)
    bob.color(red,green,blue)
