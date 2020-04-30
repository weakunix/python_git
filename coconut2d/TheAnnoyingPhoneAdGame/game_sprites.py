import cocos
import pyglet


def makeCursor():
    cursorR = pyglet.image.load("cursor_1.png")
    cursorR.anchor_x = cursorR.width // 2
    cursorR.anchor_y = cursorR.height // 2
    default_cursor = pyglet.window.ImageMouseCursor(cursorR, 0, 0)
    return default_cursor
