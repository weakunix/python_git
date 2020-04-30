# Imports
import cocos
import pyglet
# Files
import game_menu
import game_sprites

# end of imports
# g-Vars
sceneNumber = 0


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


# start
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
    ttl = game_menu.printTitle()
    btn1 = game_menu.buttonStart()
    # sprites

    # scenes
    # menu
    menuScene = cocos.scene.Scene()
    menuScene.add(bg)
    menuScene.add(ttl)
    menuScene.add(btn1)
    # game
    gameScene = cocos.scene.Scene()
    gameScene.add(bg)
    gameScene.add(sS)
    # run
    # menu scene
    if sceneNumber == 0:
        cocos.director.director.run(menuScene)
    if sceneNumber == 1:
        cocos.director.director.pop(menuScene)
        cocos.director.director.replace(gameScene)
        cocos.director.director.push(gameScene)


def start():
    global sceneNumber
    sceneNumber = 1
