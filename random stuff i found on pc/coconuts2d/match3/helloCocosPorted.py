import cocos


class HelloCoconut(cocos.layer.Layer):
    def __init__(self):
        super().__init__()
        label = cocos.text.Label("Hello Coconut", font_name="Times New Roman", font_size=32,
                                 anchor_x="center", anchor_y="center")
        label.position = 640, 360
        self.add(label)


if __name__ == "__main__":
    cocos.director.director.init(width=1280, height=720, caption="My coconut: is a big bi(n)g nut")
    hello_layer = HelloCoconut()
    test_scene = cocos.scene.Scene(hello_layer)

    cocos.director.director.run(test_scene)