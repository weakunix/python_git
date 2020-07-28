import turtle, random, math

def mandle(a, b, c, d, n):
    real = c ** 2 - d ** 2 + a
    img = 2 * c * d + b
    c = real
    d = img
    if n > 1 and distance(c, d) < 2:
        return mandle(a, b, c, d, n - 1)
    else:
        return c, d

def distance(a, b):
    try:
        return math.sqrt(a ** 2 + b ** 2)
    except:
        return 2

bob = turtle.Turtle()
bob.hideturtle()
bob.penup()
scream = turtle.Screen()
scream.setup(700, 500)
scream.tracer(10000)
for i in range(80000):
    x = random.randint(-375, 375)
    y = random.randint(-250, 250)
    xcor = (x - 125) / 250
    ycor = y / 250
    if distance(*mandle(xcor, ycor, xcor, ycor, 15)) < 2:
        bob.setpos(x, y)
        bob.dot(2, 'black')
