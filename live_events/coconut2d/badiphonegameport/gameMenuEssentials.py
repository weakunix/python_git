# Imports
import cocos
import pyglet
# Files
import gameClasses

# end of imports
# g-Vars
isSquare = input("square puzzle?")  # asks if puzzle is square
if isSquare[0] == "y" or isSquare[0] == "Y":
    sizeOfGameX = int(input("difficulty? (for both x and y)  10 atmost is recommended"))
    sizeOfGameY = int(sizeOfGameX)
else:
    sizeOfGameX = int(input("difficulty X? 10 atmost is recommended"))  # makes input x length playing area
    sizeOfGameY = int(input("difficulty Y?  10 atmost is recommended"))  # makes input y width playing area

gameArray = gameClasses.createArray(sizeOfGameX, sizeOfGameY)


# print(gameArray)


# everything about menu screen
class buttonStart(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super().__init__()
        btn = pyglet.image.load("btnsheet.png")
        btn_sliced = pyglet.image.ImageGrid(btn, 1, 2, item_width=102, item_height=51)
        self.anim = pyglet.image.Animation.from_image_sequence(btn_sliced[0:], 0, loop=False)
        self.anim1 = pyglet.image.Animation.from_image_sequence(btn_sliced[1:], 0, loop=False)
        self.btn = cocos.sprite.Sprite(self.anim, anchor=(0, 0))
        size = cocos.director.director.get_window_size()
        self.btn.position = (560, 240)
        self.btn.scale = 2
        self.add(cocos.text.Label(
            "The Annoying Phone Game",
            position=(size[0] / 2, size[1] / 1.5),
            font_name="Comic Sans",
            font_size=20,
            anchor_x="center",
            anchor_y="center"
        ))
        self.add(self.btn)
        self.clicked = False

    def on_mouse_press(self, x, y, button, modifiers):
        if button & pyglet.window.mouse.LEFT:
            if gameClasses.aOnB(x, y, 0, 0, self.btn.x, self.btn.y, self.btn.width, self.btn.height):
                self.clicked = True
                print("game starts")
                cocos.director.director.replace(gameScene)

    def on_mouse_motion(self, x, y, dx, dy):
        if gameClasses.aOnB(x, y, 0, 0, self.btn.x, self.btn.y, self.btn.width, self.btn.height):
            self.btn.image = self.anim1
        else:
            self.btn.image = self.anim


def stuff(gameScene):
    gameScene.add(gameClasses.showScore())
    gameScene.add(gameClasses.playground())
    gameClasses.makeIntroArray(sizeOfGameX, sizeOfGameY)
    gameClasses.arrayToShapes(gameArray, gameScene)


if __name__ == "__main__":
    cocos.director.director.init(width=1280, height=720, caption="The Annoying Phone Game")

    # cursor
    cursor = gameClasses.makeCursor()
    cocos.director.director.window.set_mouse_cursor(cursor)

    # sprites and scenes
    # menu
    menuScene = cocos.scene.Scene()
    # background
    menuScene.add(gameClasses.Background())
    # button to start
    menuScene.add(buttonStart())
    # game
    gameScene = cocos.scene.Scene()
    # background
    gameScene.add(gameClasses.Background())
    # score display
    stuff(gameScene)
    # run
    cocos.director.director.run(menuScene)
    # menu scene
    # changeSceneThread = threading.Thread(target=changeScene(), daemon=True)
    # changeSceneThread.start()
