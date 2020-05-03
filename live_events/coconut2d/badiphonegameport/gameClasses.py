import cocos
import pyglet
from pyglet.window import key
from pyglet.window import mouse
import random

# global var
gameStuff = [0 for x in range(100)]
n = 0
size = 66
cursorR = ""


# custom cursor
def makeCursor():
    global cursorR
    cursorR = pyglet.image.load("cursor_1.png")
    cursorR.blit(66, 66)
    cursorR.anchor_x = cursorR.width // 2
    cursorR.anchor_y = cursorR.height // 2
    default_cursor = pyglet.window.ImageMouseCursor(cursorR, 0, 0)
    return default_cursor


# Essentials
class showScore(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        label = cocos.text.Label(
            "Score:",
            font_name="Times New Roman",
            font_size=20,
            anchor_x="center",
            anchor_y="center"
        )
        size = cocos.director.director.get_window_size()
        print(size)
        label.position = size[0] / 15, size[1] / 1.1
        self.add(label)


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
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.cub = pyglet.image.ImageGrid(pyglet.image.load("diamondSprite.png"), 1, 2, item_width=124, item_height=124)
        self.anim = pyglet.image.Animation.from_image_sequence(self.cub[1:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.cub[0:], 0, loop=False)
        self.cDiamond = cocos.sprite.Sprite(self.anim, anchor=(0, 0))
        self.cDiamond.scale = 0.5
        self.add(self.cDiamond)

    def positionMake(self, x, y):
        self.cDiamond.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cursorR.width, cursorR.height, self.cDiamond.x, self.cDiamond.y, self.cDiamond.width,
                self.cDiamond.height):
            self.cDiamond.image = self.anim1
        else:
            self.cDiamond.image = self.anim


class cubeCircle(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.cirimg = pyglet.image.ImageGrid(pyglet.image.load("circleSprite.png"), 1, 2, item_width=124,
                                             item_height=124)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.cirimg[0:], 0, loop=False)
        self.anim = pyglet.image.Animation.from_image_sequence(self.cirimg[1:], 0, loop=False)
        self.cCircle = cocos.sprite.Sprite(self.anim, anchor=(0, 0))
        self.cCircle.scale = 0.5
        self.add(self.cCircle)

    def positionMake(self, x, y):
        self.cCircle.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cursorR.width, cursorR.height, self.cCircle.x, self.cCircle.y, self.cCircle.width,
                self.cCircle.height):
            self.cCircle.image = self.anim1
        else:
            self.cCircle.image = self.anim


class cubeTriangle(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.tri = pyglet.image.ImageGrid(pyglet.image.load("triangleSprite.png"), 1, 2, item_width=124,
                                          item_height=124)
        self.anim = pyglet.image.Animation.from_image_sequence(self.tri[1:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.tri[0:], 0, loop=False)
        self.cTriangle = cocos.sprite.Sprite(self.anim, anchor=(0, 0))
        self.cTriangle.scale = 0.5
        self.add(self.cTriangle)

    def positionMake(self, x, y):
        self.cTriangle.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cursorR.width, cursorR.height, self.cTriangle.x, self.cTriangle.y, self.cTriangle.width,
                self.cTriangle.height):
            self.cTriangle.image = self.anim1
        else:
            self.cTriangle.image = self.anim


class cubeStar(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        self.sta = pyglet.image.ImageGrid(pyglet.image.load("starSprite.png"), 1, 2, item_width=124, item_height=124)
        self.anim = pyglet.image.Animation.from_image_sequence(self.sta[1:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(self.sta[0:], 0, loop=False)
        self.cStar = cocos.sprite.Sprite(self.anim, anchor=(0, 0))
        self.cStar.scale = 0.5
        self.add(self.cStar)

    def positionMake(self, x, y):
        self.cStar.position = (x, y)  # change this later when algorithm comes out

    def on_mouse_motion(self, x, y, dx, dy):
        if aOnB(x, y, cursorR.width, cursorR.height, self.cStar.x, self.cStar.y, self.cStar.width, self.cStar.height):
            self.cStar.image = self.anim1
        else:
            self.cStar.image = self.anim


def createArray(diff):
    gameArray = [[random.randint(0, 3) for x in range(0, diff)] for y in range(0, diff)]
    return gameArray


def aOnB(x, y, w, h, ax, ay, aw, ah):
    if ax + aw > x + w > ax:
        if ay + ah > y + h > ay:
            return True
    return False


def aTouchB(x, y, w, h, ax, ay, aw, ah):#fix
    if x + w >= ax + aw >= x and y + h >= ay + ah >= y or ax + aw >= x + w >= ax and ay + ah >= y + h >= ay:
        return True
    return False


def makeSpriteCube(gameArrayArgument, x, y, gameScene):
    global gameStuff
    global n
    global size
    ex = (x * size) + 310
    why = (y * size) + 40
    if gameArrayArgument == 0:
        gameStuff[n] = cubeCircle()
        gameStuff[n].positionMake(ex, why)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to circle
    elif gameArrayArgument == 1:
        gameStuff[n] = cubeStar()
        gameStuff[n].positionMake(ex, why)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to star
    elif gameArrayArgument == 2:
        gameStuff[n] = cubeTriangle()
        gameStuff[n].positionMake(ex, why)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to triangle
    elif gameArrayArgument == 3:
        gameStuff[n] = cubeDiamond()
        gameStuff[n].positionMake(ex, why)
        gameScene.add(gameStuff[n])
        n += 1
        # pass  # set to diamond
    # return gameStuff


def arrayToShapes(diff, gameArray, gameScene):
    for i in range(len(gameArray)):
        for ii in range(len(gameArray[i])):
            # print(
            makeSpriteCube(gameArray[i][ii], i, ii, gameScene)
            # )


if __name__ == "__main__":
    print("wrong file. This isn't the one to run")
