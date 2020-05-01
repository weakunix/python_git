# Imports
import cocos
import pyglet
import threading
# Files
import game_menu
import game_sprites


# end of imports
# g-Vars
arrayOfScenes = ["",""]

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


# everything about menu screen
class buttonStart(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        btn = pyglet.image.load("btnsheet.png")
        btn_sliced = pyglet.image.ImageGrid(btn, 1, 2, item_width=102, item_height=51)
        anim = pyglet.image.Animation.from_image_sequence(btn_sliced[0:], 1, loop=True)
        self.spr = cocos.sprite.Sprite(anim, anchor=(0, 0))
        size = cocos.director.director.get_window_size()
        self.spr.position = (size[0] / 2)-self.spr.width, size[1] / 3
        self.spr.scale = 2
        self.add(cocos.text.Label(
            "The Annoying Phone Game",
            position=(size[0] / 2, size[1] / 1.5),
            font_name="Comic Sans",
            font_size=20,
            anchor_x="center",
            anchor_y="center"
        ))
        self.add(self.spr)
        self.clicked = False

    def MouseOnSprite(self, x, y):
        if self.spr.x + self.spr.width > x > self.spr.x:
            if self.spr.y + self.spr.height > y > self.spr.y:
                return True
        return False

    def on_mouse_press(self, x, y, button, modifiers):
        if button & pyglet.window.mouse.LEFT:
            if self.MouseOnSprite(x, y):
                self.clicked = True
                print("game starts")
                cocos.director.director.replace(gameScene)


if __name__ == "__main__":
    cocos.director.director.init(width=1280, height=720, caption="The Annoying Phone Game")

    # cursor
    cursor = game_sprites.makeCursor()
    cocos.director.director.window.set_mouse_cursor(cursor)
    # background
    bg = Background()
    # score
    sS = showScore()
    # title screen
    #btn1 = game_menu.buttonStart()
    btn1 = buttonStart()
    # sprites

    # scenes
    # menu
    menuScene = cocos.scene.Scene()
    menuScene.add(bg)
    menuScene.add(btn1)
    # game
    gameScene = cocos.scene.Scene()
    gameScene.add(bg)
    gameScene.add(sS)
    # run
    cocos.director.director.run(menuScene)
    # menu scene
    # changeSceneThread = threading.Thread(target=changeScene(), daemon=True)
    # changeSceneThread.start()
