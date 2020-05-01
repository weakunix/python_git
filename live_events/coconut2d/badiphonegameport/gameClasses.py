import cocos
import pyglet
import random


# custom cursor
def makeCursor():
    cursorR = pyglet.image.load("cursor_1.png")
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
        self.playground.scale = 0.75
        size = cocos.director.director.get_window_size()
        self.playground.position = (size[0] / 2, size[1] / 2)
        self.add(self.playground)


# diamond cube
class cubeDiamond(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        cub = pyglet.image.ImageGrid(pyglet.image.load("diamondSprite.png"), 1, 2, item_width=124, item_height=124)
        anim = pyglet.image.Animation.from_image_sequence(cub[0:], 5, loop=True)
        self.cDiamond = cocos.sprite.Sprite(anim, anchor=(0, 0))
        self.cDiamond.position = (400, 200)  # change this later when algoritem comes out
        self.cDiamond.scale = 0.25
        self.add(self.cDiamond)


class cubeCircle(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        cirimg = pyglet.image.ImageGrid(pyglet.image.load("circleSprite.png"), 1, 2, item_width=124, item_height=124)
        anim = pyglet.image.Animation.from_image_sequence(cirimg[0:], 5, loop=True)
        self.cCircle = cocos.sprite.Sprite(anim, anchor=(0, 0))
        self.cCircle.position = (440, 200)  # change this later when algoritem comes out
        self.cCircle.scale = 0.25
        self.add(self.cCircle)


class cubeTriangle(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        tri = pyglet.image.ImageGrid(pyglet.image.load("triangleSprite.png"), 1, 2, item_width=124, item_height=124)
        anim = pyglet.image.Animation.from_image_sequence(tri[0:], 5, loop=True)
        self.cTriangle = cocos.sprite.Sprite(anim, anchor=(0, 0))
        self.cTriangle.position = (510, 200)  # change this later when algoritem comes out
        self.cTriangle.scale = 0.25
        self.add(self.cTriangle)


class cubeStar(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        sta = pyglet.image.ImageGrid(pyglet.image.load("starSprite.png"), 1, 2, item_width=124, item_height=124)
        anim = pyglet.image.Animation.from_image_sequence(sta[0:], 5, loop=True)
        self.cStar = cocos.sprite.Sprite(anim, anchor=(0, 0))
        self.cStar.position = (480, 200)  # change this later when algoritem comes out
        self.cStar.scale = 0.25
        self.add(self.cStar)


def createArray(diff):
    gameArray = [[random.randint(0, 3) for x in range(0, diff)]for y in range(0, diff)]
    return gameArray


if __name__ == "__main__":
    print("wrong file. This isn't the one to run")
