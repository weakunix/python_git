import cocos
from cocos.director import director
import pyglet
from pyglet.window import key


class Mover(cocos.actions.Move):
    def step(self, dt):
        super().step(dt)
        vel_x = (keyboard[key.RIGHT]-keyboard[key.LEFT]) * 500
        vel_y = (keyboard[key.UP] - keyboard[key.DOWN]) * 500
        self.target.velocity = (vel_x, vel_y)


class Cow1(cocos.layer.Layer):
    def __init__(self):
        super().__init__()

        img = pyglet.image.load("cowsheet.png")
        img_grid = pyglet.image.ImageGrid(img, 1, 35, item_width=400, item_height=400)

        anim = pyglet.image.Animation.from_image_sequence(img_grid[0:], 0.1, loop=True)

        spr = cocos.sprite.Sprite(anim)
        spr.position = 200, 500
        spr.velocity = (0, 0)

        spr.do(Mover())

        self.add(spr)


class Background(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        bg = cocos.sprite.Sprite("white.png")
        size = cocos.director.director.get_window_size()
        bg.position = size[0]/2, size[1]/2
        self.add(bg)


if __name__ == "__main__":
    director.init(width=1280, height=720, caption="Tutorial 1: My Cocos Window")
    director.window.pop_handlers()

    keyboard = key.KeyStateHandler()
    director.window.push_handlers(keyboard)

    spr2_layer = Cow1()
    backGroundSprite = Background()

    test_scene = cocos.scene.Scene()
    test_scene.add(spr2_layer, 1, "cow")
    test_scene.add(backGroundSprite, 0, "background")

    director.run(test_scene)