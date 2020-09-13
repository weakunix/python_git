#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.floatlayout import FloatLayout
from kivy.properties import ObjectProperty

class Touch(Widget):
    btn = ObjectProperty()

    def on_touch_down(self, touch):
        print("mouse down", touch)
        self.btn.opacity = 0.5
    def on_touch_move(self, touch):
        print("hes on da move!", touch)
    def on_touch_up(self, touch):
        print("mouse up", touch)
        self.btn.opacity = 1

class MyddApp(App):
    def build(self):
        return Touch()

#main
if __name__ == '__main__':
    MyddApp().run()
