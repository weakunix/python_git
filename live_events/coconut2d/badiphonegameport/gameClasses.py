import cocos
import pyglet


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


class playground(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        self.playground = cocos.sprite.Sprite(pyglet.image.load(
            "playground.png"))
        self.playground.scale = 0.75
        size = cocos.director.director.get_window_size()
        self.playground.position = (size[0] / 2, size[1] / 2)
        self.add(self.playground)
