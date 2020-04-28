import cocos
from cocos.director import director


class Enemy(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        spr = cocos.sprite.Sprite("enemy.png")

        spr.position = 400, 360

        self.add(spr)


class Background(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        bg = cocos.sprite.Sprite("white.png")
        size = cocos.director.director.get_window_size()
        bg.position = size[0]/2, size[1]/2
        self.add(bg)


class Player1(cocos.sprite.Sprite):
    def __init__(self):
        super().__init__("cow.png")

        self.position = 640, 360


if __name__ == "__main__":
    director.init(width=1280, height=720, caption="Tutorial 1: My Cocos Window")
    director.window.pop_handlers()

    spr1_layer = Enemy()
    spr2_layer = Player1()
    backGroundSprite = Background()

    test_scene = cocos.scene.Scene()
    test_scene.add(spr1_layer, 1, "cow enemy")
    test_scene.add(spr2_layer, 1, "cow")
    test_scene.add(backGroundSprite, 0, "background")

    director.run(test_scene)