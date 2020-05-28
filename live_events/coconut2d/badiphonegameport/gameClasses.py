import cocos
import pyglet
from pyglet.window import key
from pyglet.window import mouse
import random

# global var

gameStuff = []  # stuff
sizeOfGameX = 0  # game horiz space
sizeOfGameY = 0  # game vert space
gameAray = []  #
gameScene: str = ""  # gameScene which has the elements to add to


# make the array based on len and wid passed in
def makeIntroArray(aLength, aWidth):
    global gameStuff
    global sizeOfGameX
    global sizeOfGameY
    sizeOfGameX = aLength
    sizeOfGameY = aWidth
    gameStuff = [0 for x in range(aLength * aWidth)]


# Turn the array just made into a new grid.
def createArray(diffx, diffy):
    global gameAray
    gameArray = [[random.randint(0, 3) for x in range(0, diffx)] for y in range(0, diffy)]
    return gameArray


n = 0  # counter for an array
size = 66  # size of a block
cursorR = ""  # cursor
scorePoints = 0  # points
cL = 0  # length cursor
cW = 0  # width cursor


# custom cursor
def makeCursor():
    global cursorR
    cursorR = pyglet.image.load("cursor_1.png")
    cursorR.anchor_x = 66
    cursorR.anchor_y = 66
    default_cursor = pyglet.window.ImageMouseCursor(cursorR, 0, 0)
    return default_cursor


# Essentials
# shows score
class showScore(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        global scorePoints
        self.label = cocos.text.Label(
            text=("Score:" + str(scorePoints)),  # update
            font_name="Times New Roman",
            font_size=20,
            anchor_x="center",  # overlapping
            anchor_y="center"
        )
        size = cocos.director.director.get_window_size()  # window size
        # print(size)
        self.label.position = size[0] / 15, size[1] / 1.1  # where the showscore is
        self.add(self.label)
        # self.add(self.label1)

    def update(self):
        self.label = cocos.text.Label(
            text=("Score:" + str(scorePoints)),  # update
            font_name="Times New Roman",
            font_size=20,
            anchor_x="center",
            anchor_y="center"
        )


# background
class Background(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        img = cocos.sprite.Sprite("background.jpg")
        img.scale = 1
        img.position = img.width // 2, img.height // 2

        self.px_width = 1366
        self.px_height = 768

        self.add(img)


# the big rant screen
class playground(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        self.playground = cocos.sprite.Sprite(pyglet.image.load(
            "playground.png"))
        self.playground.scale = 1
        size = cocos.director.director.get_window_size()
        self.playground.position = (size[0] / 2, size[1] / 2)
        self.add(self.playground)


# diamond cube
class cubeDiamond(cocos.layer.Layer):
    is_event_handler = True  # can be clicked on

    def __init__(self):
        super().__init__()
        self.cub = pyglet.image.ImageGrid(pyglet.image.load("diamondSprite.png"), 1, 2, item_width=124,
                                          item_height=124)  # get picture
        self.anim = pyglet.image.Animation.from_image_sequence(self.cub[1:], 0, loop=False)  # slice it
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.cub[0:], 0, loop=False)  # slice the other one
        self.cDiamond = cocos.sprite.Sprite(self.anim)  # make sprite with animation just sliced
        self.cDiamond.scale = 0.5  # scale it down
        self.posx = 0  # no place yet
        self.posy = 0  # no place yet
        self.add(self.cDiamond)  # compile to frame

    def positionMake(self, x, y):
        self.cDiamond.position = (x, y)  # changes location when arry made

    def on_mouse_motion(self, x, y, dx, dy):  # if mouse over this
        if aOnB(x, y, cL, cW, self.cDiamond.x, self.cDiamond.y, self.cDiamond.width,
                self.cDiamond.height):
            self.cDiamond.image = self.anim1  # switch frames
        else:
            self.cDiamond.image = self.anim

    def on_mouse_press(self, x, y, button, modifiers):
        if aOnB(x, y, cL, cW, self.cDiamond.x, self.cDiamond.y, self.cDiamond.width,
                self.cDiamond.height):
            # if(
            check(self.posx, self.posy)  # chceck if the block clicked is clear

    def posInArray(self, p1, p2, n):  # position in array (to see what to clear)
        self.posx = p1
        self.posy = p2
        self.n = n


# circle cube
class cubeCircle(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.cirimg = pyglet.image.ImageGrid(pyglet.image.load("circleSprite.png"), 1, 2, item_width=124,
                                             item_height=124)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.cirimg[0:], 0, loop=False)
        self.anim = pyglet.image.Animation.from_image_sequence(self.cirimg[1:], 0, loop=False)
        self.cCircle = cocos.sprite.Sprite(self.anim)
        self.cCircle.scale = 0.5
        self.posx = 0
        self.posy = 0
        self.n = 0
        self.add(self.cCircle)

    def posInArray(self, p1, p2, n):
        self.posx = p1
        self.posy = p2
        self.n = n

    def positionMake(self, x, y):
        self.cCircle.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cL, cW, self.cCircle.x, self.cCircle.y, self.cCircle.width,
                self.cCircle.height):
            self.cCircle.image = self.anim1
        else:
            self.cCircle.image = self.anim

    def on_mouse_press(self, x, y, button, modifiers):
        if aOnB(x, y, cL, cW, self.cCircle.x, self.cCircle.y, self.cCircle.width,
                self.cCircle.height):
            check(self.posx, self.posy)


class cubeTriangle(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.tri = pyglet.image.ImageGrid(pyglet.image.load("triangleSprite.png"), 1, 2, item_width=124,
                                          item_height=124)
        self.anim = pyglet.image.Animation.from_image_sequence(self.tri[1:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.tri[0:], 0, loop=False)
        self.cTriangle = cocos.sprite.Sprite(self.anim)
        self.cTriangle.scale = 0.5
        self.posx = 0
        self.posy = 0
        self.n = 0
        self.add(self.cTriangle)

    def positionMake(self, x, y):
        self.cTriangle.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cL, cW, self.cTriangle.x, self.cTriangle.y, self.cTriangle.width,
                self.cTriangle.height):
            self.cTriangle.image = self.anim1
        else:
            self.cTriangle.image = self.anim

    def on_mouse_press(self, x, y, button, modifiers):
        if aOnB(x, y, cL, cW, self.cTriangle.x, self.cTriangle.y, self.cTriangle.width,
                self.cTriangle.height):
            check(self.posx, self.posy)

    def posInArray(self, p1, p2, n):
        self.posx = p1
        self.posy = p2
        self.n = n


class resetBtn(cocos.layer.Layer):
    is_event_handler = True
    global sizeOfGameY
    global gameAray
    global gameScene
    global sizeOfGameX

    def __init__(self):
        super().__init__()
        self.res = pyglet.image.ImageGrid(pyglet.image.load("resetbtn.png"), 1, 2, item_width=132, item_height=132)
        self.anim = pyglet.image.Animation.from_image_sequence(self.res[0:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.res[1:], 0, loop=False)
        self.cRes = cocos.sprite.Sprite(self.anim)
        ize = cocos.director.director.get_window_size()
        self.cRes.position = (ize[0] / 1.1, ize[1] / 1.1)
        self.cRes.scale = 0.5
        self.add(self.cRes)

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cL, cW, self.cRes.x, self.cRes.y, self.cRes.width, self.cRes.height):
            self.cRes.image = self.anim1
        else:
            self.cRes.image = self.anim

    def on_mouse_press(self, x, y, button, modifiers):
        if aOnB(x, y, cL, cW, self.cRes.x, self.cRes.y, self.cRes.width,
                self.cRes.height):
            gameAray = createArray(sizeOfGameX, sizeOfGameY)
            arrayToShapes(gameAray, gameScene)
            # pass


class cubeStar(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.sta = pyglet.image.ImageGrid(pyglet.image.load("starSprite.png"), 1, 2, item_width=124, item_height=124)
        self.anim = pyglet.image.Animation.from_image_sequence(self.sta[1:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.sta[0:], 0, loop=False)
        self.cStar = cocos.sprite.Sprite(self.anim)
        self.cStar.scale = 0.5
        self.posx = 0
        self.posy = 0
        self.n = 0
        self.add(self.cStar)

    def positionMake(self, x, y):
        self.cStar.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cL, cW, self.cStar.x, self.cStar.y, self.cStar.width, self.cStar.height):
            self.cStar.image = self.anim1
        else:
            self.cStar.image = self.anim

    def posInArray(self, p1, p2, n):
        self.posx = p1
        self.posy = p2
        self.n = n

    def on_mouse_press(self, x, y, button, modifiers):
        if aOnB(x, y, cL, cW, self.cStar.x, self.cStar.y, self.cStar.width,
                self.cStar.height):
            check(self.posx, self.posy)


def aOnB(x, y, w, h, ax, ay, aw, ah):
    if ax + aw > x + w > ax:
        if ay + ah > y + h > ay:
            return True
    return False


def aTouchB(x, y, w, h, ax, ay, aw, ah):  # fix
    pass


def check(x, y):
    global gameAray  # takes globals game cubes
    # print(gameAray[x][y])
    # print(x, y)
    if x != sizeOfGameX - 1 and y != sizeOfGameY - 1 and x != 0 and y != 0:  # if x and y ain't at borders
        # if gameAray[x][y] == gameAray[x + 1][y] and gameAray[x][y] == gameAray[x - 1][y] and gameAray[x][y] ==
        # gameAray[x][y + 1] and gameAray[x][y] == gameAray[x][y - 1]: gravity(True, x, y) #if both
        if gameAray[x][y] == gameAray[x + 1][y] and gameAray[x][y] == gameAray[x - 1][y]:
            gravity(False, x, y)
        if gameAray[x][y] == gameAray[x][y + 1] and gameAray[x][y] == gameAray[x][y - 1]:
            gravity(True, x, y)
    elif x == sizeOfGameX - 1 and y == sizeOfGameY - 1:  # if borders
        print("border")
    elif x == 0 and y == sizeOfGameY - 1:
        print("border")
    elif x == sizeOfGameX - 1 and y == 0:
        print("border")
    elif x == 0 and y == 0:
        print("border")
    elif x == sizeOfGameX - 1 or x == 0:  # if edge
        if gameAray[x][y] == gameAray[x][y + 1] and gameAray[x][y] == gameAray[x][y - 1]:
            gravity(True, x, y)  # only vert check
    elif y == sizeOfGameY - 1 or y == 0:  # if edge
        if gameAray[x][y] == gameAray[x + 1][y] and gameAray[x][y] == gameAray[x - 1][y]:
            gravity(False, x, y)  # only do horiz check


def gravity(verticle, x, y):  # bugged
    global gameAray
    global gameScene
    global scorePoints
    # shift down
    if verticle:  # if it was vert clear
        #for i in range(0, 3):
        for num in range(y):
            # gameAray[x][0] = random.randint(0, 3)
            # if y-num >= 0:
            if num == y:
                gameAray[x][0] = random.randint(0, 3)  # fucccing works
                gameAray[x][1] = random.randint(0, 3)
                gameAray[x][2] = random.randint(0, 3)
            elif num == 0:
                gameAray[x][y - num + 1] = gameAray[x][y - num - 2]
                gameAray[x][y - num] = gameAray[x][y - num - 3]
                gameAray[x][y - num - 1] = gameAray[x][y - num - 4]
            else:
                gameAray[x][y - num - 2] = gameAray[x][y - num - 5]
            # else:

            # gameAray[x][1] = random.randint(0, 3)
            # gameAray[x][2] = random.randint(0, 3)
        scorePoints += 100
        # print(scorePoints)
    elif not verticle:
        for num in range(y):
            if num == y:
                gameAray[x][0] = random.randint(0, 3)  # fuccing broken
                gameAray[x + 1][0] = random.randint(0, 3)
                gameAray[x - 1][0] = random.randint(0, 3)
            else:
                gameAray[x + 1][y - num] = gameAray[x + 1][y - num - 1]  # fine
                gameAray[x][y - num] = gameAray[x][y - num - 1]  # fine
                gameAray[x - 1][y - num] = gameAray[x - 1][y - num - 1]  # fine
        scorePoints += 100
        # print(scorePoints)
    # print(gameAray)
    arrayToShapes(gameAray, gameScene)  # updates the shapes


def makeSpriteCube(gameArrayArgument, x, y, gameScene):
    global gameStuff
    global n
    global size
    makeIntroArray(sizeOfGameX, sizeOfGameY)
    ex = (x * size) + 345
    why = 650 - (y * size)  # 65
    # 65
    if gameArrayArgument == 0:
        gameStuff[n] = cubeCircle()
        gameStuff[n].positionMake(ex, why)
        gameStuff[n].posInArray(x, y, n)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to circle
    elif gameArrayArgument == 1:
        gameStuff[n] = cubeStar()
        gameStuff[n].positionMake(ex, why)
        gameStuff[n].posInArray(x, y, n)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to star
    elif gameArrayArgument == 2:
        gameStuff[n] = cubeTriangle()
        gameStuff[n].positionMake(ex, why)
        gameStuff[n].posInArray(x, y, n)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to triangle
    elif gameArrayArgument == 3:
        gameStuff[n] = cubeDiamond()
        gameStuff[n].positionMake(ex, why)
        gameStuff[n].posInArray(x, y, n)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to diamond
    # return gameStuff


def arrayToShapes(gameArray, gameScene1):
    global n
    global gameAray
    global gameScene
    n = 0
    gameScene = gameScene1
    gameAray = gameArray
    for ii in range(len(gameArray)):  # i
        for i in range(len(gameArray[ii])):  # ii,i
            makeSpriteCube(gameArray[i][ii], i, ii, gameScene)
    updateScore(gameScene)


def updateScore(gameScene):
    b = showScore()
    b.update()
    r = resetBtn()
    gameScene.add(b)
    gameScene.add(r)


if __name__ == "__main__":
    print("wrong file. This isn't the one to run")
