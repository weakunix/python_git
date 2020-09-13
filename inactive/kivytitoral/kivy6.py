#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout


class MydApp(App):
    def build(self):
        return FloatLayout()

#main
if __name__ == '__main__':
    MydApp().run()
