import cocos
from cocos.director import director
import pyglet
from pyglet.window import key
from pyglet.window import mouse

# custom cursors
cursorR = pyglet.image.load("crosshair_for_regular.png")
cursorR.anchor_x = cL // 2
cursorR.anchor_y = cW // 2
default_cursor = pyglet.window.ImageMouseCursor(cursorR, 0, 0)
cursorH = pyglet.image.load("hover_crosshair.png")
cursorH.anchor_x = cursorH.width // 2
cursorH.anchor_y = cursorH.height // 2
hover_cursor = pyglet.window.ImageMouseCursor(cursorH, 0, 0)


class Mover(cocos.actions.Move):
    def step(self, dt):
        super().step(dt)
        vel_x = (keyboard[key.D] - keyboard[key.A]) * 250
        vel_y = (keyboard[key.W] - keyboard[key.S]) * 250
        self.target.velocity = (vel_x, vel_y)
        scroller.set_focus(self.target.x, self.target.y)


class Cow1(cocos.layer.ScrollableLayer):
    is_event_handler = True

    def __init__(self):
        super().__init__()

        img = pyglet.image.load("cowsheet.png")
        img_grid = pyglet.image.ImageGrid(img, 1, 35, item_width=400, item_height=400)

        # anim = pyglet.image.Animation.from_image_sequence(img_grid[0:], 0.1, loop=True)
        anim = pyglet.image.Animation.from_image_sequence(img_grid[0:], 0, loop=False)

        self.spr = cocos.sprite.Sprite(anim, anchor=(0, 0))
        self.spr.position = 0, 0
        self.spr.velocity = (0, 0)
        self.spr.scale = 0.25
        self.spr.do(Mover())
        self.add(self.spr)
        self.clicked = False

    def mouseonsprite(self, x, y):
        if self.spr.x + self.spr.width > x > self.spr.x:
            if self.spr.y + self.spr.height > y > self.spr.y:
                return True
        return False

    def on_mouse_drag(self, x, y, dx, dy, button, modifiers):
        if self.clicked:
            self.spr.position = (x, y)

    def on_mouse_press(self, x, y, button, modifiers):
        if button & mouse.LEFT:
            self.clicked = True
            print("change to attack")
            print(self.mouseonsprite(x, y))
        elif button & mouse.RIGHT:
            print("change to shield")

    def on_mouse_release(self, x, y, button, modifiers):
        self.clicked = False

    def on_mouse_motion(self, x, y, dx, dy):
        if self.mouseonsprite(x, y):
            #cursor = director.window.get_system_mouse_cursor(director.window.CURSOR_CROSSHAIR)
            director.window.set_mouse_cursor(hover_cursor)
        else:
            #cursor = director.window.get_system_mouse_cursor(director.window.CURSOR_DEFAULT)
            director.window.set_mouse_cursor(default_cursor)


class Background(cocos.layer.ScrollableLayer):
    def __init__(self):
        super().__init__()
        bg = cocos.sprite.Sprite("backgroundtest.png")
        bg.scale = 2.0

        bg.position = bg.width // 2, bg.height // 2

        self.px_width = 2400
        self.px_height = 2400

        self.add(bg)


if __name__ == "__main__":
    director.init(width=1280, height=720, caption="Tutorial 1: My Cocos Window")
    director.window.pop_handlers()

    keyboard = key.KeyStateHandler()
    director.window.push_handlers(keyboard)

    player = Cow1()
    bg_layer = Background()

    scroller = cocos.layer.ScrollingManager()
    scroller.add(bg_layer)
    scroller.add(player)

    test_scene = cocos.scene.Scene()
    test_scene.add(scroller)

    director.run(test_scene)
