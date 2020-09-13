import cocos
from cocos.director import director
import pyglet
from pyglet.window import key


class Mover(cocos.actions.Move):
    def step(self, dt):
        super().step(dt)
        vel_x = (keyboard[key.RIGHT]-keyboard[key.LEFT]) * 250
        vel_y = (keyboard[key.UP] - keyboard[key.DOWN]) * 250
        self.target.velocity = (vel_x, vel_y)
        scroller.set_focus(self.target.x, self.target.y)


class Cow1(cocos.layer.ScrollableLayer):
    def __init__(self):
        super().__init__()

        img = pyglet.image.load("cowsheet.png")
        img_grid = pyglet.image.ImageGrid(img, 1, 35, item_width=400, item_height=400)

        #anim = pyglet.image.Animation.from_image_sequence(img_grid[0:], 0.1, loop=True)
        anim = pyglet.image.Animation.from_image_sequence(img_grid[0:], 0, loop=False)

        spr = cocos.sprite.Sprite(anim)
        spr.position = 200, 500
        spr.velocity = (0, 0)
        spr.scale = 0.25

        #if(spr.position[0] >= 0 and spr.position[0]<= 2400 and spr.position[1] >= 0 and spr.position[1]<= 2400):
        spr.do(Mover())

        self.add(spr)


class Background(cocos.layer.ScrollableLayer):
    def __init__(self):
        super().__init__()
        bg = cocos.sprite.Sprite("backgroundtest.png")
        bg.scale = 2.0

        bg.position = bg.width//2, bg.height//2

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