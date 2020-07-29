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
scream.colormode(255)

def mandledraw(DEPTH, centerx, centery, zoom):
    red = random.randint(0, 255)
    green = random.randint(0, 255)
    blue = random.randint(0, 255)
    randcolor = (red, green, blue)
    for x in range(-375, 375, 6):
        for y in range(-250, 250, 6):
            xcor = (x + centerx + 125) / (250 * zoom)
            ycor = (y + centery) / (250 * zoom)
            if distance(*mandle(xcor, ycor, xcor, ycor, DEPTH)) < 2:
                bob.setpos(x, y)
                bob.dot(4, randcolor)
centerx = 0
centery = 0
ZOOM = 1
mandledraw(12, centerx, centery, ZOOM)

def get_mouse_click_coord(x, y):
    bob.clear()
    global ZOOM, centerx, centery
    print(x, y)
    centerx += x
    centery += y
    ZOOM *= 1.5
    mandledraw(12, centerx, centery, ZOOM)

scream.onscreenclick(get_mouse_click_coord)
scream.listen()
